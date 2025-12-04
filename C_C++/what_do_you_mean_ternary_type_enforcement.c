// @BAKE gcc -o $*.out $@ -std=c23
void f(void *) { ; }

signed main(void) {
    int i = 0;
    int h = 0;
    double d = 1.0f;

    //f(( 1 ? &i : &h));
    //f(( 1 ? &i : &d));

    int k = (int)((
        (1 ? ((typeof(i)*)nullptr) : ((typeof(d)*)nullptr)),
        i
    ));

    return 0;
}
