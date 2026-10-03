// @BAKE gcc -o $*.out $@ -std=c23 -Wall
// unsuccessful attempt to prevent macro expansions
#include "stdio.h"

#define PASTE(a, b) a ## b
#define QUOTE(x) PASTE(x, )

void a(void) { ; }
void b(void) { ; }

signed main(void) {
    printf("%p vs %p\n", (void*)a, (void*)b);

    #define a b

    printf("%p\n", (void*)QUOTE(a));

    return 0;
}
