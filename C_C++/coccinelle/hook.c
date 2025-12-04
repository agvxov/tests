// @BAKE gcc -fPIC -shared -o lib$*.so $@
#include <stdio.h>

void f(void) {
    puts("Evil.");
}

void h(void) {
    puts("Evil.");
}
