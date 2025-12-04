#include <stdio.h>

signed main(void) {
    const char * a = "nigger";

    auto b = 1 ? &a : (typeof("a"+0)*)("a"+0);
}
