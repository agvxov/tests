// @BAKE gcc $@ -o $*
signed main(void) {
    const char * suffix = "cpp";

    if (suffix[0] == "cxx"[0]
    &&  suffix[1] == "cxx"[1]
    &&  suffix[2] == "cxx"[2]) {
        return 1;
    }

    return 0;
}
