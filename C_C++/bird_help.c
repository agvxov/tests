// @BAKE $CC -o $*.out $@
#include <stdio.h>

signed main(void) {
    int had_blank = 0;

    int c;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (!had_blank) {
                putchar(c);
                had_blank = 1;
            }
        }
        // else { // since you dont have else yet
        if (c != ' ') {
            putchar(c);
            had_blank = 0;
        }
    }

    return 0;
}
