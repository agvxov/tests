//@BAKE gcc -o $*.out $@ -ggdb
#include <stdio.h>
#include "array2.h"

signed main(void) {
    a2_t(char) buffer;
    a2_init(char, buffer, 5, 6);

    for (int i = 0; i < 5; i++) {
        for (int h = 0; h < 5; h++) {
            buffer[i][h] = 'A' + i*5 + h;
        }
        buffer[i][5] = '\n';
    }

    fputs(*buffer, stdout);

    a2_destroy(buffer);
    return 0;
}
