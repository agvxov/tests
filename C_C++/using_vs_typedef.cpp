// @BAKE g++ -o $*.out $@

class A {
 public:
    typedef int my_int_1; // i assumed typedef does not scope either; but then, why not just adopt it to support template syntax?
    using my_int_2 = int;
};

signed main(void) {
    A::my_int_1 i;
    A::my_int_2 h;
    return 0;
}
