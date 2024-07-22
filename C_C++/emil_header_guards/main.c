// @BAKE gcc main.c -o $*.out
#if 0
# include "a.h"
# include "b.h"
#else
# include "ac.h"
# include "bc.h"
#endif

signed main() {
    return 0;
}
