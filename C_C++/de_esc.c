// @BAKE gcc -o $*.out $@ -ldictate -ggdb -Wall -Wpedantic
#include <dictate.h>

char * deescape_backslash(char * s) {
    /* NOTE: Fish always escapes backslashes in its history file;
     *        that is, they always come in pairs, i.e. "\\".
     */
    char * si = s;
    for (char * ss = s; *ss != '\0'; si++, ss++) {
        switch (*ss) {
            case '\\': {
                ++ss;
            } break;
        }
        *si = *ss;
    }
    *si = '\0';

    return s;
}

signed main(void) {
    char test[] = "this \\\\is \\\\my te\\\\\\\\st string\\\\";
    deescape_backslash(test);

    dictate(test);

    return 0;
}
