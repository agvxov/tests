/* C23 MOGS C++
 */
#if 1
// @BAKE gcc -o $*.out $@ -std=c23
struct {int x; int y;} f(void) {
    typeof(f()) r;
    r.x = 1;
    r.y = 0;
    return r;
}

signed main(void) {
    return f().y;
}
/* Works, no questions asked (wife material).
 */
#else
// @BAKE g++ -o $*.out $@
struct a {int x; int y;} f(void) {
    decltype(f()) r;
    r.x = 1;
    r.y = 0;
    return r;
}

signed main(void) {
    return f().y;
}

/* output:
 * c23-tuple-return.c:15:1: error: new types may not be defined in a return type
 * 15 | struct {int x; int y;} f(void) {
 *    | ^~~~~~
 * c23-tuple-return.c:15:1: note: (perhaps a semicolon is missing after the definition of ‘<unnamed struct>’)
 */

/* She wants me to use an std::tuple, ew!
 */

#endif

// WOOAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH BUDYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
// I rest my case.
