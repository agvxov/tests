// @BAKE gcc $@ -o $*.out -ggdb -O0

void a() {
    int dummy;
    const char * i = &dummy - sizeof(const char *);
    puts(i);
}

signed main() {
    a("test");
}
