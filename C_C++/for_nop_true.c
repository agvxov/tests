// @BAKE gcc -O0 $@ -o $*.out -g; objdump -d $*.out
main() {
    int a = 2;
    for (; a == 1;) {
        ;
    }

    for (;;) {
        ;
    }
}
