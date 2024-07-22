// @BAKE gcc $@ -o $*.out $(pkg-config --cflags --libs ncurses)
#include <ncurses.h>

char * own_source(void) {
	FILE* f = fopen("ncurses_labels.c", "r");
	fseek(f, 0, SEEK_END);
	int flen = ftell(f);
	rewind(f);
	char * buffer = calloc(flen+1, sizeof(char));
	fread(buffer, flen, sizeof(char), f);
	fclose(f);
	return buffer;
}

signed main() {
	slk_init(3);

	initscr();
	noecho();
	cbreak();
	WINDOW * win = newwin(0, 0, 0, 0);
	nodelay(win, TRUE);
	keypad(win, TRUE);
	refresh();

	slk_set(1,  "exit", 0);
	slk_refresh();


	waddstr(win, own_source());
	wrefresh(win);
	int do_run = TRUE;
	while (do_run) {
		if (wgetch(win) == KEY_F(1)) {
			do_run = FALSE;
		}
	}

	endwin();
	return 0;
}
