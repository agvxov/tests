// @COMPILECMD g++ $@ $(pkg-config --libs ncurses)
#include <signal.h>
#include <ncurses.h>

int scr_h, scr_w;
WINDOW* myWindow;
char greeting[] = "Hello Ncurses!";

void display(int sig = 0){
	if(sig != 0){
		delwin(myWindow);
		endwin();
		refresh();
		clear();
	}
    getmaxyx(curscr, scr_h, scr_w);
    myWindow = newwin(3, ( sizeof(greeting)-1 ) + 4, 
    		( scr_h / 2 ) - 1, (scr_w - ( sizeof(greeting)-1) ) / 2);
    refresh();

    box(myWindow, 0, 0);
    mvwaddstr(myWindow, 1, 2, greeting);
    wrefresh(myWindow);
}

signed main(){
    initscr();
    noecho();
    curs_set(0);
	signal(SIGWINCH, display);

	display();
    while(1){}

    endwin();
    return 0;
}

