/* @BAKE gcc $@ -o $*.out $(pkg-config --cflags --libs ncurses) && ./$*.out
 */
#include <stdio.h>
#include <ncurses.h>

signed main() {
    /* Irrelevant */
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    nodelay(stdscr, true);
    scrollok(stdscr, true);
    /* ---------- */
    void recieve() {
        addstr("Recieved a message.\n");
    }
    void block() {
        addstr("A message was blocked.\n");
    }

    void (*strategizing_function)(void) = recieve;

    while (1) {
        char c = wgetch(stdscr);
        if (c != EOF) {
            strategizing_function = (strategizing_function == recieve ? block : recieve);
        }
        strategizing_function();
        napms(500);
    }
}
