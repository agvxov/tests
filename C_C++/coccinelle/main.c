// @BAKE gcc -o $*.out $@ libhook.so
#include <stdio.h>

void f(void) {
    puts("Good.");
}

signed main(void) {
    f();

    return 0;
}
