// @BAKE g++ $@ -o $*.out
#include <stdio.h>
#include <iostream>

signed main() {
    unsigned long i = 60 * 1000;
    printf("%lu\n", i);
    std::cout << i << std::endl;
}
