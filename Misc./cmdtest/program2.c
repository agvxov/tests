// @BAKE gcc $@ -o $*.out
signed main(int argc, char * argv[]) {
    return !fopen(argv[1], "r");
}
