#include <iostream>
#include <ncurses.h>

int main(){
	initscr();

	printw("this is a message\ncontinueing");
	std::cout << "cout";
	refresh();

	getch();

	endwin();
	return 0;
}
