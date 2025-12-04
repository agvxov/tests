// @BAKE clang -E -o $*.out $@

//#define wrench(i) struct { int a; int b; } // OK
//#define wrench(i) (0, 1) // OK
//#define wrench(i) (a, b) // OK
//#define wrench(i) ({a, b}) // OK
//#define wrench(i) struct { int a, b; } // BOOM
#define wrench(i) 0, 1 // BOOM

#define L(i) 0
#define proxy(i) L(i)
#define entry(i) proxy(wrench(i))

signed main(void) {
    return entry(int);
}
