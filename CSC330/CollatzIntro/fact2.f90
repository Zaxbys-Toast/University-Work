program fact2
    implicit none
    integer(kind=8) :: val, i

    do i = 1, 20  ! Increase the range to compute more factorials
        call fact(i, val)
        print *, i, val
    end do
end program fact2

recursive subroutine fact(i, val)
    implicit none
    integer(kind=8), intent(in) :: i
    integer(kind=8), intent(out) :: val

    if (i > 1) then
        call fact(i - 1, val)
        val = val * i
    else
        val = 1
    end if
end subroutine fact

