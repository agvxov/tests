/* @BAKE
    gcc -o $*.out $@ -std=c23 -ggdb
    gcc -fPIC -shared -o lib$@.so main2.c -std=c23 -ggdb
   @STOP
*/
#include "hot.h"

#include <stdio.h>

void h(void) {
    puts("Good.");
}

void f(void) {
    puts("Good.");
}

signed main(void) {
    hot_init(SO_NAME(__FILE__));

    while (true) {
        hot_rebind();

        h();
        f();
    }

    return 0;
}
