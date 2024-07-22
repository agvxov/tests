// @BAKE gcc $@ sds/sds.c -o $* -ggdb
#include <stdio.h>
#include <string.h>
#include "sds/sds.h"

signed main() {
    char * str = "this string";
    str = strncat(str, "\0is short", 9);
    printf("%s|%s\n", str, str + 12);

    sds s = sdsnew("this string");
    printf("%ld\n", sdslen(s));
    s = sdscatlen(s, "\0 is long", 9);
    printf("%ld\n", sdslen(s));
}
