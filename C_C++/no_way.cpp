// @BAKE g++ $@ -O1 -Wall
#include <iostream>

int main() {
    while (1)
        ;
}

void unreachable() {
    std::cout << "Hello world!" << std::endl;
}

/*
    clang version 18.1.5
    Target: x86_64-pc-linux-gnu
    Thread model: posix
    InstalledDir: /usr/lib/llvm/18/bin
    Configuration file: /etc/clang/x86_64-pc-linux-gnu-clang.cfg

    $ a.out
    Hello world!
*/
