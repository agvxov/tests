// @BAKE g++ $@ -o $*.out $(pkg-config --cflags --libs ncurses) && xterm -e $PWD/$*.out
#include <ncurses.h>

signed main() {
    initscr();
    raw();
    keypad(stdscr, true);
    while (true) {
        int c = wgetch(stdscr);
        move(0, 0);
        clrtoeol();
        printw("%d", c);
    }
}
