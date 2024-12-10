// @BAKE gcc $@
#include <stdlib.h>

void test(const char * i) {
    free(i);
}

signed main() {
    free("test");
    test("test");
}
