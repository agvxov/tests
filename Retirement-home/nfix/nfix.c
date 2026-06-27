// @BAKE gcc -o $* $@ $(pkg-config --cflags --libs ncurses)
#include <stdio.h>
#include <ncurses.h>

signed main(){
    initscr();

    echo();
    curs_set(1);
    nocbreak();

    endwin();

    fputs("\033[2 q", stdout);
    fflush(stdout);

    return 0;
}
