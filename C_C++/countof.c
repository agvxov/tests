// @BAKE gcc -o $*.out $@ -std=c23
#include <stdio.h>

#define _is_static_array(A) \
    _Generic(&(A), typeof(&(A)[0])*: 0, default: 1)

#define _assert_static_array(A) \
    ((void)sizeof(char[1 - 2 * !_is_static_array(A)]))

#define countof(A) ( \
    _assert_static_array(A), \
    (sizeof(A) / sizeof(A[0])) \
)

#define countof_unsafe(A) \
    (sizeof(A) / sizeof(A[0]))

signed main(void) {
    char s[10];
    char d[2][2];
    char (*p)[10] = &s;
    char * k = d[0];

    printf("%d\n", _is_static_array(s));
    printf("%d\n", _is_static_array(d));
    printf("%d\n", _is_static_array(p));
    printf("%d\n", _is_static_array(k));

    puts("---");

    printf("%d\n", (int)countof(s));
    printf("%d\n", (int)countof(d));
    //printf("%d\n", (int)countof(p)); // wont compile
    //printf("%d\n", (int)countof(k)); // wont compile

    return 0;
}
