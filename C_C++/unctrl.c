// @COMPILECMD gcc $@ -o $* $(pkg-config --cflags --libs ncurses)
#include <stdio.h>
#include <ncurses.h>

void main() {
	puts(unctrl("test"));
}
