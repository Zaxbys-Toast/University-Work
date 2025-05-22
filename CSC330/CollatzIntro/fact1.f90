program fact1

integer :: val, i
integer :: fact
external fact

do i = 1, 13
  print *, i, fact(i)
enddo

end program fact1


recursive integer function fact( i ) result (val)

integer :: i

if ( i /= 1 ) then
  val = i * fact(i-1)
else
  val = 1
  return
endif

end function fact

