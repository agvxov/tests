// @COMPILECMD g++ $@ -o $*.out -ggdb $(pkg-config --cflags --libs ncurses)
#include <sys/param.h>	// MAX()
#include <math.h>
#include <ncurses.h>

typedef struct {
	int y;
	int x;
} spatial;

void dda(const char c, const spatial from, const spatial to) {
	const int steps = MAX(abs(to.y - from.y), abs(to.x - from.x));

	struct {
		double y;
		double x;
	} d = {
		.y = (double)from.y,
		.x = (double)from.x,
	};

	for (int i = 0; i < steps+1; i++) {
		mvaddch(round(d.y), round(d.x), c);
		d.y += (double)(to.y - from.y) / (double)steps;
		d.x += (double)(to.x - from.x) / (double)steps;
	}
	return;
}

signed main() {
	initscr();
	noecho();
	curs_set(0);

	spatial from = {6, 20};
	spatial to   = {3, 0};
	
	dda('-', from, to);

	refresh();
	while(1){}
	endwin();
	return 0;
}
