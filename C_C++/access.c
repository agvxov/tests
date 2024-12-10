// @BAKE gcc $@
#include <unistd.h>
#include <stdio.h>

int main(void) {
    const char *path = "../";

    return access(path, R_OK);
}
