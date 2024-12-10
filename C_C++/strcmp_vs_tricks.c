/* @BAKE
    watch 'gcc -o main.out main.c -O3 && objdump -d --disassemble=main main.out'
   @STOP
*/
#include <string.h>

signed main(int argc, char * argv[]) {
    const char * suffix = argv[1]; // e.g. "cxx"
    int r = 0;

    /* GCC apparently cant optimze this at all,
     * strcmp will be called
     */
    if(!strcmp(suffix, "cxx")) {
        r = 1;
    }

    /* The alternative being something inline,
     *  as explicitly typed out in cscope for example
     */
    if (suffix[0] == 'c'
    &&  suffix[1] == 'x'
    &&  suffix[2] == 'x') {
        r = 1;
    }

    return r;
}
