// @BAKE gcc -o $*.out $@ -std=c23 -Wall -Wpedantic -Wextra -Wno-override-init
#include <stdio.h>

typedef struct {
    int a;
    int b;
} f_args_t;

int f_(int i, f_args_t args) {
    int r = i + args.a + args.b;
    printf("%d\n", r);
    return r;
}

#define f(i, ...) f_(i, (f_args_t) { .a=0, .b=0, __VA_ARGS__ })

int h(int a, int b) {
    return a * b;
}

signed main(void) {
    // works
    f(1);
    // behold!
    f(1, .a=2);
    f(1, .a=2, .b=3);
    f(1, .b=3);
    // but there is a danger of you doing this by accident,
    //  it will warn, but y'know
    f(1, 2);
    // will not work, macros are a fuck
    #if 0
    f(1, .a=h(5, 6));
    #endif
    // but we are clever
    #define COMMA ,
    f(1, .a=h(5 COMMA 6));
}
