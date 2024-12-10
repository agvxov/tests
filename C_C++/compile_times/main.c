#include <stdio.h>

extern int i;

signed main() {
    for (; i < 10; i++) {
        puts("blaaablaaa");
    }

    return 0;
}
