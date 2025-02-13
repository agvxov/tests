// @BAKE gcc -o $*.out $@ -Wall -Wpedantic -std=c23 -ggdb
#include <stdio.h>

#define PRINTA_FUNCTION(T, nm, pattern) \
    static inline                               \
    int printa_ ## nm (                         \
        const T * const a,                      \
        const size_t n                          \
    ) {                                         \
        int r = 3;                              \
        fputs("[ ", stdout);                    \
        for (size_t i = 0; i < n; i++) {        \
            r += printf(pattern, a[i]);         \
        }                                       \
        putchar(']');                           \
        return r;                               \
    }

PRINTA_FUNCTION(int, int, "%d, ")
PRINTA_FUNCTION(char, char, "'%c', ")
PRINTA_FUNCTION(char*, str, "\"%s\", ")
#define printa_builtin_types_generic \
    ,int:         printa_int  \
    ,char:        printa_char \
    ,char*:       printa_str  \
    ,const char*: printa_str

#define printa(a, l) _Generic(a[0] \
        printa_builtin_types_generic \
    )(a, l)


signed main(void) {
    #define len 3
    int my_int_array[len] = {1, 2, 3};
    char my_chr_array[len] = {'a', 'b', 'c'};
    const char * my_str_array[len] = { "abc", "def", "ghi"};

    printa(my_int_array, len);
    putchar('\n');
    printa(my_chr_array, len);
    putchar('\n');
    printa(my_str_array, len);
    putchar('\n');

    return 0;
}
