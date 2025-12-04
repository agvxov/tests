// @BAKE swig -c++ -c $@
%module a

//%inline %{
////# include "a.hpp"
//class MyClass {
//    int i;
//  public:
//    int f() { return i + 1; }
//};
//
//void f() { return 1; }
//%}

%include "a.hpp"
