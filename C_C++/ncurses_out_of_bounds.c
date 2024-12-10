// @BAKE g++ $@ -o $*.out $(pkg-config --cflags --libs ncurses)
#include <ncurses.h>

int scr_h, scr_w;
char greeting[] = "Hello Ncurses!";

signed main(){
    initscr();
    noecho();
    curs_set(0);


    getmaxyx(stdscr, scr_h, scr_w);
    WINDOW* myWindow = newwin(3, (sizeof(greeting)-1) + 4, 20, 80);
    refresh();

    while(1) {
        mvaddstr(10, 80, greeting);

        box(myWindow, 0, 0);
        mvwaddstr(myWindow, 1, 2, greeting);
        wrefresh(myWindow);
        refresh();
    }

    endwin();
    return 0;
}
