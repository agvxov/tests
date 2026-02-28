// @BAKE gcc -o $*.out $@ -std=c23 -Wall -Wpedantic
#include <stdio.h>

signed main(void) {
    /* Anonymous structs are great for macro hacks.
     * However, it is impossible to create another object
     *  that *technically* shares their type.
     * According to the standard,
     *  two equivalent anonymous structs only merge into the same type if
     *  they are from different compilation units.
     * Note that this is disputed by Clang, because the working is non-obvious.
     * Anyways, assignment to self + the coma operator allows us to execute arbitary code
     *  at the declaration of a anonymous struct, which might be required for
     *  foreach type hacks
     */
    struct {
        int i, h;
    } i = (i.i = 14, i);

    printf(" -- %d\n", i.i);

    return 0;
}
