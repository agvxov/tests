// @BAKE clang -o $*.out $@ -L/home/anon/Swap/libmill/.libs/ -l:libmill.a -I/home/anon/Swap/libmill/ -ggdb
//#include <math.h>
#include <stdio.h>
#include <libmill.h>

//coroutine
//void producer(int j) { 
//    //const size_t target = 1'000'000'000;
//    const size_t target = 1000000000;
//    for (size_t i = 1; i < target; i++) {
//        int ignore = sin(0.5) * i * cos(1/i);
//    }
//}

coroutine
void status_reporter(void) {
    
}

signed main(void) {
    //do {
    //    void *mill_sp;
    //    mill_ctx ctx = mill_getctx_();
    //    if(!mill_setjmp_(ctx)) {
    //        mill_sp = mill_prologue_(MILL_HERE_);
    //        int mill_anchor[mill_unoptimisable1_];
    //        mill_unoptimisable2_ = &mill_anchor;
    //        char mill_filler[(char*)&mill_anchor - (char*)(mill_sp)];
    //        mill_unoptimisable2_ = &mill_filler;
    //        producer(1);
    //        mill_epilogue_();
    //    }
    //} while(0);
    //go(producer(1));
    go(status_reporter());

    return 0;
}

/*
    literally anything i try segfaults; offical tests included
    this line seems to be at fault:
        `char mill_filler[(char*)&mill_anchor - (char*)(mill_sp)];`
    my best guess is that my hardened kernel does not like being rawdogged like that?
*/
