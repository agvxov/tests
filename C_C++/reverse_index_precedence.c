// @BAKE gcc -o $*.out $@ -ldictate -std=c2x
#include <dictate.h>
signed main(void) {
    int guard = 4;
    int array[] = { 1, 2, 3 };

    dictate(
        (-1)[array],
        //-1[array],
        "\n"
    );

    return 0;
}
