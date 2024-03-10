// @BAKE g++ $@ $(pkg-config --cflags --libs menu ncurses); ./a.out
#include <stdio.h>
#include "menu.h"

int main() {
    printf("E_NOT_CONNECTED: %d\n", E_NOT_CONNECTED);
    printf("E_SYSTEM_ERROR: %d\n", E_SYSTEM_ERROR);
    printf("E_OK: %d\n", E_OK);
    printf("E_BAD_ARGUMENT: %d\n", E_BAD_ARGUMENT);
    printf("E_POSTED: %d\n", E_POSTED);

    return 0;
}
