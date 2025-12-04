// @BAKE gcc -o $*.out $@ -std=c23 -ldictate && ./$*.out
#include <dictate.h>

signed main(void) {
    mdictate("### ",
        "There are ", 2, " hard problems in programming:\n",
        0, ") naming things\n",
        1, ") cache misses\n",
        2, ") off by one errors\n"
    );
    return 0;
}
