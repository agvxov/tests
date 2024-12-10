/* This compiles with gcc, but not g++.
 * `extern "C"` apparently only applies to calling conventions.
 * It's nothing horrid, but I'm still disappointed.
 */
extern "C" {
    signed main() {
        int * a = malloc(10);
    }
}
