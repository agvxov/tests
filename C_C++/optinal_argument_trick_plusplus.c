// @BAKE gcc -o $*.out $@ -std=c23
typedef struct {
    int b;
    int c;
} args_t;

void f_(int a, args_t args, ...) { ; }

#define I }
#define f(a, ...) \
    f_(             \
        a,          \
        (args_t) {  \
            .b = 0, \
            .c = 0, \
        __VA_ARGS__ \
    )               \

signed main(void) {
    f(1, I);
    f(1, I, 80, 100);
    f(1, .b=2, .c=3, I, 80, 100);
    return 0;
}
