// @BAKE g++ $@ -o ncurses_pufka_example.out $(pkg-config --cflags --libs ncurses)
#include <ncurses.h>

int scr_h, scr_w;
char greeting[] = "Hello Ncurses!";

signed main(){
    initscr();
	start_color();
    noecho();
    curs_set(0);

    getmaxyx(stdscr, scr_h, scr_w);
    WINDOW* myWindow = newwin(3, ( sizeof(greeting)-1 ) + 4, 
    		( scr_h / 2 ) - 1, (scr_w - ( sizeof(greeting)-1) ) / 2);
	init_pair(1, COLOR_RED, COLOR_BLUE);
	wbkgd(myWindow, COLOR_PAIR(1));
    refresh();

    box(myWindow, 0, 0);
    mvwaddstr(myWindow, 1, 2, greeting);
    wrefresh(myWindow);

    while(1){}

    endwin();
    return 0;
}
