// @BAKE gcc $@ -std=c23

const char i[] = {
#   embed "is_embed_finally_here.c"
};

signed main(void) { ; }
