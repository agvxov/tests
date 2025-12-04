// @BAKE gcc -o $*.out $@ -Wall -Wpedantic -Wextra -O3
#include <stdio.h>

typedef struct {
    int i;
    int h;
} A;

signed main(void) {
    A a = (A) {
        .i = 0,
        .h = 0,
    };

    a = (A) {
        .h = a.i,
        .i = 3,
    };

    A b = {
        .i = 128,
        .h = b.i,
    };

    A c = {
        .h = 128,
        .i = c.h,
    };

    printf("{ .i = %d, .h = %d }\n", a.i, a.h);
    printf("{ .i = %d, .h = %d }\n", b.i, b.h);
    printf("{ .i = %d, .h = %d }\n", c.i, c.h);

    return 0;
}
