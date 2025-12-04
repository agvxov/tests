// @BAKE gcc $@ -std=c23
#include <stdio.h>

const char i[] = {
#   embed "is_embed_finally_here.c"
};

signed main(void) {
    puts(i);
}
