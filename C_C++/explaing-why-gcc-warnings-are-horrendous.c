typedef struct {
    int i;
} mystruct;

signed main(void) {
    auto a = (mystruct) {
        .i = 1,
    };
    return 0;
}

/* # Works perfectly
 * $ gcc a.c -Wpedantic
 *
 * # Warns
 * $ g++ a.c -Wpedantic
 * a.c: In function ‘int main()’:
 * a.c:7:9: warning: C++ designated initializers only available with ‘-std=c++20’ or ‘-std=gnu++20’ [-Wc++20-extensions]
 *     7 |         .i = 1,
 *       |         ^
 * a.c:8:5: warning: ISO C++ forbids compound-literals [-Wpedantic]
 *     8 |     };
 *       |     ^
 *
 * ---
 *
 * As you can see, the compound-literal warning is bound to -Wpedantic,
 *  but -Wpedantic is a group, so its either all or nothing.
 * The objectively correct way to go about is always providing a specific flag,
 *  like clang does:
 * $ clang++ a.c -Wpedantic
 * clang++: warning: treating 'c' input as 'c++' when in C++ mode, this behavior is deprecated [-Wdeprecated]
 * a.c:6:14: warning: compound literals are a C99-specific feature [-Wc99-extensions]
 *     6 |     auto a = (mystruct) {
 *       |              ^
 * a.c:7:9: warning: designated initializers are a C++20 extension [-Wc++20-designator]
 *     7 |         .i = 1,
 *       |         ^
 * 2 warnings generated.
 */
