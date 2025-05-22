program collatz
    implicit none
    integer :: min_range, max_range
    integer :: i, length
    integer, allocatable :: idx(:), len(:), tmp_arr(:)
    integer :: tmp_idx, tmp_len, j
    character(len=32) :: arg_min, arg_max

    ! Retrieve command-line arguments as strings
    call get_command_argument(1, arg_min)
    call get_command_argument(2, arg_max)

    ! Convert strings to integers
    read(arg_min, *) min_range
    read(arg_max, *) max_range

    ! Check if range values are valid
    if (min_range >= max_range) then
        print *, "minRange must be less than maxRange"
        stop
    end if

    ! Initialize arrays for lengths and indices (fixed size for top 10)
    allocate(len(10))
    allocate(idx(10))
    len = 0
    idx = 0

    ! Iterate through the range
    do i = min_range, max_range - 1
        length = find_length(i, 0)

        ! Check if the current length should be added to the top 10
        if (i <= 10) then
            ! Initially fill the arrays with the first 10 values
            len(i) = length
            idx(i) = i
        else
            ! If the length is greater than the smallest in len, replace it
            tmp_len = minval(len)  ! Find the minimum value in len
            if (length > tmp_len) then
                tmp_arr = minloc(len)  ! Find the index of the minimum value
                tmp_idx = tmp_arr(1)   ! Get the scalar index from minloc
                len(tmp_idx) = length  ! Replace the smallest value with the current length
                idx(tmp_idx) = i       ! Replace the corresponding index
            end if
        end if
    end do

    ! Sort by sequence length (descending)
    call sort_by_length(len, idx)

    print *, "Sorted based on sequence length:"
    do j = 1, size(len)
        print *, idx(j), len(j)
    end do

    ! Sort by integer size (index)
    call sort_by_index(len, idx)

    print *, "Sorted based on integer size:"
    do j = 1, size(idx)
        print *, idx(j), len(j)
    end do

contains

    ! Recursive function to find the Collatz sequence length
    recursive function find_length(i, length) result(res)
        integer, intent(in) :: i, length
        integer :: res

        if (i == 1) then
            res = length
        elseif (mod(i, 2) == 0) then
            res = find_length(i / 2, length + 1)
        else
            res = find_length(i * 3 + 1, length + 1)
        end if
    end function find_length

    ! Sort by sequence length (descending)
    subroutine sort_by_length(len, idx)
        integer, dimension(:), intent(inout) :: len
        integer, dimension(:), intent(inout) :: idx
        integer :: i, j, tmp_len, tmp_idx

        do i = 1, size(len) - 1
            do j = i + 1, size(len)
                if (len(i) < len(j)) then
                    tmp_len = len(i)
                    tmp_idx = idx(i)
                    len(i) = len(j)
                    idx(i) = idx(j)
                    len(j) = tmp_len
                    idx(j) = tmp_idx
                end if
            end do
        end do
    end subroutine sort_by_length

    ! Sort by integer size (index)
    subroutine sort_by_index(len, idx)
        integer, dimension(:), intent(inout) :: len
        integer, dimension(:), intent(inout) :: idx
        integer :: i, j, tmp_len, tmp_idx

        do i = 1, size(idx) - 1
            do j = i + 1, size(idx)
                if (idx(i) < idx(j)) then
                    tmp_len = len(i)
                    tmp_idx = idx(i)
                    len(i) = len(j)
                    idx(i) = idx(j)
                    len(j) = tmp_len
                    idx(j) = tmp_idx
                end if
            end do
        end do
    end subroutine sort_by_index

end program collatz
