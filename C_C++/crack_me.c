// @BAKE gcc $@ -o $*.out
#include <stdio.h>
#include <string.h>

void bad_function(void) {
    puts("Sorry, this is the bad function.");
    puts("Try: 'crack_me.out <correct-password>'");
}

void good_function(void) {
    puts("Yay! This is the good function");
}

signed main(int argc, char * * argv) {
    if (argc < 2
    || !strcmp(argv[1], "mysecretpassword")) {
        bad_function();
    } else {
        good_function();
    }

    return 0;
}
