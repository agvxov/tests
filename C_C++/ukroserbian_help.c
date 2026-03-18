// @BAKE gcc -o $*.out $@ -Wall -Wpedantic
signed main(void) {
    int i = 0;
    if (i = 1) {
        return 1;
    }
    return 0;
}
/*
output: ukroserbian_help.c: In function ‘main’:
help.c:4:9: warning: suggest parentheses around assignment used as truth value [-Wparentheses]
    4 |     if (i = 1) {
      |         ^
*/
