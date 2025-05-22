program readtest

    character(80) :: lineOfText
    character(len=*), parameter :: filename="testhands"
    character(len=*), parameter :: path="/pub/pounds/CSC330/poker/"
    character(:), allocatable :: fullpath

    ! Concatenate the path and filename together
    fullpath = path // filename

    open(unit=5,file=fullpath,status="old")
    do i = 1, 6
        read (5,"(a80)") lineOfText
        print *, lineOfText
    enddo
    close(5)

end program readtest
