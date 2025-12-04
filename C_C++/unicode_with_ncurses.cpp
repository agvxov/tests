#include <ncurses.h>

int scr_h, scr_w;
char greeting[] = "¤äđálaűű¤";

signed main(){
    initscr();
    noecho();
    curs_set(0);

    getmaxyx(stdscr, scr_h, scr_w);
    addstr(greeting);
	refresh();

    while(1){}

    endwin();
    return 0;
}
