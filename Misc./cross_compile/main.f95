program HelloWorld
  use iso_c_binding

  interface
    function newthing() bind(c) result(result)
      import
      type(c_ptr) :: result
    end function newthing
    subroutine queryi() bind(c)
    end subroutine queryi
    subroutine queryh() bind(c)
    end subroutine queryh
  end interface

  type(c_ptr) :: t;
  t = newthing()

  stop 42;
end program HelloWorld
