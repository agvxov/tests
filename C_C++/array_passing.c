#include <stdio.h>

// im shocked that this thing even compiles, and slightly disappointed that it doesnt solve anything
void f(int n, int a[n]) {
    printf("%d\n", sizeof(a));
}

signed main(void) {
    int a[8];
    printf("%d\n", sizeof(a));
    f(8, a);
    return 0;
}
