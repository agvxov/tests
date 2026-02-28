// @BAKE gcc -o $*.out $@ -O0 -ggdb -Wall -Wpedantic
#include <stdio.h>


signed main(void) {
    size_t my_size;
    /* This is UB.
     * GNU decided that it should wrap instead of erroring out...
     */
    [[ maybe_unused ]] auto e = sscanf("-1", "%zu", &my_size);
    return 0;
}
