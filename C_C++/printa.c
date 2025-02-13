// @BAKE gcc -o $*.out $@ -Wall -Wpedantic -std=c23 -ggdb

#include <stdio.h>
#include <string.h>

#define STRINGIFY(x) #x
#define printa(T, a, n) _printa(STRINGIFY(T), (char*)a, n) 

int _printa(const char * mytypename, char * a, size_t n) {
    int r = sizeof("[ ]")-1; // minimum output on success
    const char * type_format;
    size_t type_size;
    
    if (0) { ;
    } else if (!strcmp(mytypename, "int")) {
        type_format = "%d, ";
        type_size   = sizeof(int);
    } else if (!strcmp(mytypename, "char")) {
        type_format = "'%c', ";
        type_size   = sizeof(char);
    } else if (!strcmp(mytypename, "char*")) {
        type_format = "\"%s\", ";
        type_size   = sizeof(char*);
    } else {
        return 0;
    }

    fputs("[ ", stdout);
    for (size_t i = 0; i < n; i++) {
        r += printf(type_format, *(int**)(a + (type_size*i)));
    }
    putchar(']');

    return r;
}

signed main(void) {
    #define len 3
    int my_int_array[len] = {1, 2, 3};
    char my_chr_array[len] = {'a', 'b', 'c'};
    const char * my_str_array[len] = { "abc", "def", "ghi"};

    printa(int, my_int_array, len);
    putchar('\n');
    printa(char, my_chr_array, len);
    putchar('\n');
    printa(char*, my_str_array, len);
    putchar('\n');

    return 0;
}
