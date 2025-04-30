/* @BAKE
    gcc $@ -o $*.out -ggdb
    valgrind --tool=callgrind $*.out
   @STOP
 */
#include <stdio.h>
signed main(void) {
    puts("hw");
    return 0;
}
