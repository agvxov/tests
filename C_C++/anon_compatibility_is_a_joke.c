// @BAKE clang -o $*.out $@ -std=c23
signed main(void) {
    {
        struct A { int a; };
        struct A my_A;
        struct A * A_ptr = &my_A;
    }

    {
        struct { int b; } my_B;
        struct { int b; } * B_ptr = &my_B;
    }

    return 0;
}
