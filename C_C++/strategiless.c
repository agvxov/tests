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
    bool is_blocking = false;

    while (1) {
        char c = wgetch(stdscr);
        if (c != EOF) {
            is_blocking = !is_blocking;
        }
        if (!is_blocking) {
            addstr("Recieved a message.\n");
        } else {
            addstr("A message was blocked.\n");
        }
        napms(500);
    }
}
