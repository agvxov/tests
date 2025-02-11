// @BAKE gcc -o AppDir/$*.out $@
#include <stdio.h>

signed main(void) {
    FILE * f = fopen("/var/db/repos/gentoo/header.txt", "r");
    if (!f) { return 1; }

    for (int c = fgetc(f); c != EOF; c = fgetc(f)) {
        putchar(c);
    }

    fclose(f);
    return 0;
}
