program FooBar
  integer :: i
  do i = 1, 100
    if (MOD(i, 3) == 0 .and. MOD(i, 5) == 0) then
      write(*,*) "FizzBuzz"
    else if (MOD(i, 3) == 0) then
      write(*,*) "Fizz"
    else if (MOD(i, 5) == 0) then
      write(*,*) "Buzz"
    else
      write(*,*) i
    end if
  end do
end program FooBar
