/* @BAKE
    gcc -o $* $@
    strace ./opener
   @STOP
 */
// NOTE: this file is for testing strace, not C
#include <fcntl.h>
signed main() { open("example.txt", O_CREAT | O_WRONLY); }
