program collatz
    use iso_fortran_env, only: int64
    implicit none

    type :: CollatzValue
        integer(int64) :: value
        integer(int64) :: c_length
    end type CollatzValue

    integer(int64) :: start_val, stop_val
    integer :: narg
    character(len=128) :: arg1, arg2

    call get_command_argument(1, arg1)
    call get_command_argument(2, arg2)

    if (len_trim(arg1) == 0 .or. len_trim(arg2) == 0) then
        print *, "Usage: ./fixed <start> <end>"
        stop
    end if

    read(arg1,*) start_val
    read(arg2,*) stop_val

    call computeCollatzInRange(start_val, stop_val)

contains

    function get_length(i) result(len)
        integer(int64), intent(in) :: i
        integer(int64) :: len, x

        x = i
        len = 1_int64
        do while (x /= 1_int64)
            if (mod(x, 2_int64) == 0_int64) then
                x = x / 2_int64
            else
                x = x * 3_int64 + 1_int64
            end if
            len = len + 1_int64
        end do
    end function get_length

    subroutine computeCollatzInRange(start_val, stop_val)
        integer(int64), intent(in) :: start_val, stop_val
        type(CollatzValue), allocatable :: top_10(:)
        type(CollatzValue), allocatable :: sorted_by_length(:), sorted_by_value(:)
        type(CollatzValue) :: new_item, smallest, existing
        integer(int64) :: collatz_length, val
        integer(int64) :: i
        integer :: idx

        allocate(top_10(0)) ! start with empty array

        do i = start_val, stop_val
            val = i
            collatz_length = get_length(i)

            idx = find_same_length(top_10, collatz_length)
            if (idx > 0) then
                existing = top_10(idx)
                if (val < existing%value) then
                    call delete_at(top_10, idx)
                    new_item%value = val
                    new_item%c_length = collatz_length
                    call push_value(top_10, new_item)
                    call sort_top10(top_10)
                end if
            else
                if (size(top_10) < 10) then
                    new_item%value = val
                    new_item%c_length = collatz_length
                    call push_value(top_10, new_item)
                    call sort_top10(top_10)
                else
                    smallest = top_10(1)
                    new_item%value = val
                    new_item%c_length = collatz_length
                    if (lt(smallest, new_item)) then
                        call pop_first(top_10)
                        call push_value(top_10, new_item)
                        call sort_top10(top_10)
                    end if
                end if
            end if
        end do

        ! Sort results by length (descending) and value (ascending)
        sorted_by_length = top_10
        call sort_by_length(sorted_by_length)

        sorted_by_value = top_10
        call sort_by_value(sorted_by_value)

        print *, "Sorted by length:"
        do i = 1, size(sorted_by_length)
            print *, sorted_by_length(i)%value, sorted_by_length(i)%c_length
        end do

        print *, "Sorted by value:"
        do i = 1, size(sorted_by_value)
            print *, sorted_by_value(i)%value, sorted_by_value(i)%c_length
        end do

    end subroutine computeCollatzInRange

    logical function lt(a, b)
        type(CollatzValue), intent(in) :: a, b
        lt = (a%c_length < b%c_length) .or. (a%c_length == b%c_length .and. a%value > b%value)
    end function lt

    integer function find_same_length(arr, length_val)
        type(CollatzValue), intent(in) :: arr(:)
        integer(int64), intent(in) :: length_val
        integer :: j
        find_same_length = 0
        do j = 1, size(arr)
            if (arr(j)%c_length == length_val) then
                find_same_length = j
                exit
            end if
        end do
    end function find_same_length

    subroutine push_value(arr, val)
        type(CollatzValue), allocatable, intent(inout) :: arr(:)
        type(CollatzValue), intent(in) :: val
        type(CollatzValue), allocatable :: temp(:)
        integer :: oldsize

        oldsize = size(arr)
        allocate(temp(oldsize+1))
        if (oldsize > 0) then
            temp(1:oldsize) = arr(1:oldsize)
        end if
        temp(oldsize+1) = val
        call move_alloc(temp, arr)
    end subroutine push_value

    subroutine delete_at(arr, idx)
        type(CollatzValue), allocatable, intent(inout) :: arr(:)
        integer, intent(in) :: idx
        integer :: oldsize
        type(CollatzValue), allocatable :: temp(:)

        oldsize = size(arr)
        if (idx < 1 .or. idx > oldsize) return

        if (oldsize == 1) then
            deallocate(arr)
            allocate(arr(0))
        else
            allocate(temp(oldsize-1))
            if (idx > 1) then
                temp(1:idx-1) = arr(1:idx-1)
            end if
            if (idx < oldsize) then
                temp(idx:oldsize-1) = arr(idx+1:oldsize)
            end if
            call move_alloc(temp, arr)
        end if
    end subroutine delete_at

    subroutine pop_first(arr)
        type(CollatzValue), allocatable, intent(inout) :: arr(:)
        call delete_at(arr, 1)
    end subroutine pop_first

    subroutine sort_top10(arr)
        type(CollatzValue), intent(inout) :: arr(:)
        integer :: i, j
        type(CollatzValue) :: key

        do i = 2, size(arr)
            key = arr(i)
            j = i - 1
            do while (j >= 1 .and. lt(key, arr(j)))
                arr(j+1) = arr(j)
                j = j - 1
            end do
            arr(j+1) = key
        end do
    end subroutine sort_top10

    subroutine sort_by_length(arr)
        type(CollatzValue), intent(inout) :: arr(:)
        integer :: i, j
        type(CollatzValue) :: key
        logical :: cond

        ! Sort by (-c_length, value): largest c_length first, ties by smaller value
        do i = 2, size(arr)
            key = arr(i)
            j = i - 1
            do
                cond = ((-key%c_length) > (-arr(j)%c_length)) .or. &
                       ((-key%c_length) == (-arr(j)%c_length) .and. key%value < arr(j)%value)
                if (j >= 1 .and. cond) then
                    arr(j+1) = arr(j)
                    j = j - 1
                    if (j < 1) exit
                else
                    exit
                end if
            end do
            arr(j+1) = key
        end do
    end subroutine sort_by_length

    subroutine sort_by_value(arr)
        type(CollatzValue), intent(inout) :: arr(:)
        integer :: i, j
        type(CollatzValue) :: key

        do i = 2, size(arr)
            key = arr(i)
            j = i - 1
            do while (j >= 1 .and. key%value < arr(j)%value)
                arr(j+1) = arr(j)
                j = j - 1
            end do
            arr(j+1) = key
        end do
    end subroutine sort_by_value

end program collatz
