/* @BAKE
    gcc $@ -o $*.out -ggdb
    valgrind --tool=callgrind $*.out
   @STOP
 */
signed main(void) {
    puts("hw");
    return 0;
}
