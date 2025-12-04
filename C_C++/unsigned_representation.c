// @BAKE gcc -o $*.out $@ -std=c23
#include <stdio.h>
signed main(void) {
    // variable representing a positive whole
    unsigned i = 0b0100; // binary notation
    printf("%d\n", i);
}
