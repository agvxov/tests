namespace A {
    int i = 1;
}

namespace B {
    using namespace A;
    int f() {
        return i;
    }
}

signed main(void) {
    //int a = i; // error (based)
    return B::f();
}
