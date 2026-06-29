//@BAKE gcc -o $*.out $@ -ggdb
#include <stdio.h>
#include "array2.h"

typedef struct {
    int i;
    char c;
} A;

signed main(void) {
    a2_t(A) buffer;
    a2_init(A, buffer, 95, 55);

    for (int i = 0; i < 95; i++) {
        for (int h = 0; h < 55; h++) {
            buffer[i][h] = (A) {
                .i = i,
                .c = 'A',
            };
        }
    }

    a2_destroy(buffer);
    return 0;
}
