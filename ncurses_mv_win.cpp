// @COMPILECMD g++ ncurses_mv_win.cpp $(pkg-config --libs ncurses)
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

int scr_h, scr_w;
WINDOW* myWindow;
WINDOW* mysubWindow;

signed main(){
	int r = 0;
	initscr();
	noecho();
	curs_set(0);
	getmaxyx(stdscr, scr_h, scr_w);

	const int myWinWidth = 100;

	myWindow = newwin(0, myWinWidth,
			0, 0);
	if(!myWindow){
		r = 1;
		goto exit;
	}
	box(myWindow, 0, 0);
	refresh();

	mysubWindow = subwin(myWindow, 0, scr_w, 0, 0);
	if(!mysubWindow){
		r = 1;
		goto exit;
	}
	touchwin(myWindow);
	refresh();

	wrefresh(myWindow);
	wrefresh(mysubWindow);
	refresh();

	while(1){
		int y, x;
		getyx(mysubWindow, y, x);
		char* s;
		asprintf(&s, "%dx%d", y, x);
		mvwaddstr(mysubWindow, 1, 1, s);
		free(s);
		wrefresh(mysubWindow);

		switch(getch()){
			case 'h':
				//if(x > 0){
					mvderwin(mysubWindow, 0, 8);
				//}
				break;
			case 'l':
				//if(x < myWinWidth){
					mvderwin(mysubWindow, 0, 8);
				//}
				break;
		}
	}

	exit:
	endwin();
	return r;
}

