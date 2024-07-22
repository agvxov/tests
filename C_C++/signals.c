// @BAKE gcc $@ -o $*.out -ggdb; ./$*.out
#include <signal.h>
#include <unistd.h>

void handler(int ignore) {
    sleep(1);
    puts("Handler.");
    return;
}

void f() {
    puts("F-1 function.");
    int i = *(int*)0x0;
    puts("F-2 function.");
}

void g() {
    puts("G function.");
}

main() {
    signal(SIGSEGV, handler);

    f();
    g();
}
