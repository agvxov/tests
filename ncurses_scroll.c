// @COMPILECMD gcc $@ -o $*.out $(pkg-config --cflags --libs ncurses)
#include <ncurses.h>

void main(){
	initscr();
	noecho();
	cbreak();
	scrollok(stdscr, TRUE);

	char buf[12];
	for(int i = 0; i < 1000; i++){
		sprintf(buf, "%d", i);
		for(int h = 0; h < 4; h++){
			addstr(buf);
			addch(' ');
		}
		addch('\n');
	}

	refresh();

	while(true){
		int i = getch();
		switch(i){
			case 'j': {
				scrl(1);
			} break;
			case 'k': {
				scrl(-1);
			} break;
		}
		refresh();
	}
}
