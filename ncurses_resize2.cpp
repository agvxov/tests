// @COMPILECMD g++ $@ -o ncurses_resize_pufka_example.out $(pkg-config --libs ncurses)
#include <signal.h>
#include <ncurses.h>

int scr_h, scr_w;
WINDOW* myWindow = NULL;
char greeting[] = "Hello Ncurses!";

void display(){
	if(myWindow){
		delwin(myWindow);
		endwin();
		erase();
		refresh();
		clear();
	}


	getmaxyx(stdscr, scr_h, scr_w);
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

	display();
	while(1){
		if(wgetch(stdscr) == KEY_RESIZE){
			display();
			flushinp();
		}
	}

	endwin();
	return 0;
}
