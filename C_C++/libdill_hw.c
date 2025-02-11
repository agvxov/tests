// @BAKE gcc -o $*.out $@ /home/anon/Swap/libdill/.libs/libdill.a -I/home/anon/Swap/libdill/ -lm -std=gnu23
#include <stdio.h>
#include <math.h>
#include <libdill.h>

coroutine
void worker(int ch) {
    const size_t target = 100'000'000;
    for (size_t i = 1; i < target; i++) {
        if ((i % (target/100)) == 0) {
            int percentage = i / (target/100);
            chsend(ch, &percentage, sizeof(percentage), now() + 10);
        }
        int ignore = sin(0.5) * i * cos(1/i);
    }

    const int hundred = 100;
    chsend(ch, &hundred, sizeof(100), now() + 10);
}

coroutine
void reporter(int ch) {
    int percentage;
    while (true) {
        chrecv(ch, &percentage, sizeof(percentage), now() + 10);

        printf("\033[0G[");
        for (int i = 0; i < 10; i++) {
            printf((i < (percentage / 10)) ? "=" : " ");
        }
        printf("] %d%%", percentage);
        fflush(stdout);

        if (percentage == 100) { break; }
    }
}

int main() {
    int ch[2];
    chmake(ch);

    int b = bundle();
    bundle_go(b, worker(ch[0]));
    bundle_go(b, reporter(ch[1]));
    bundle_wait(b, -1);
    hclose(b);

    printf("\n");
    return 0;
}
