// @BAKE gcc -o $*.out $@ -O0 -ggdb
#include <stdio.h>
#include <stdlib.h>

signed main() {
  #if 0
    char * s = getenv("FALSE")
            || getenv("ALSO_FALSE")
            || getenv("EDITOR")
            || "vi"
    ;

    puts(s);
  #endif

    // ---
    typeof("a" || "b") c;
    ++c; // GNU should be optimized out from existence

    return 0;
}
