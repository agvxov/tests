// @BAKE gcc $@ -o $*.out -ggdb

signed main() {
    void * the_void = &the_void;
    return *(int*)the_void;
}
