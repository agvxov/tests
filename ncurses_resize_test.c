#include <signal.h>
#include <ncurses.h>

void handle_winch(int sig)
{
    endwin();
    refresh();
    clear();
}
int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    signal(SIGWINCH, handle_winch);

	while(true){
		mvprintw(LINES-2, 0, "Hello, world! %d:%d\n", LINES, COLS);
		refresh();
	}

    endwin();
    return 0;
}
//#include <signal.h>
//#include <ncurses.h>
//
//void sigwinch_handler(int sig) {
//    // Tell ncurses to update its internal screen size data
//    endwin();
//    refresh();
//}
//
//int main() {
//    // Initialize ncurses
//    initscr();
//    cbreak();
//    noecho();
//    curs_set(0);
//
//    // Register the SIGWINCH signal handler
//    signal(SIGWINCH, sigwinch_handler);
//
//    // Set the initial screen color and print a message
//    start_color();
//    init_pair(1, COLOR_BLUE, COLOR_TRANSPARENT);
//    bkgd(COLOR_PAIR(1));
//    printw("Hello, world!\n");
//
//    // Wait for user input
//    refresh();
//    getch();
//
//    // Resize the screen
//    endwin();
//    refresh();
//    int new_rows, new_cols;
//    getmaxyx(stdscr, new_rows, new_cols);
//    resizeterm(new_rows, new_cols);
//
//    // Update the screen color and print another message
//    init_pair(2, COLOR_RED, COLOR_TRANSPARENT);
//    bkgd(COLOR_PAIR(2));
//    printw("Goodbye!\n");
//
//    // Wait for user input
//    refresh();
//    getch();
//
//    // Clean up and exit
//    endwin();
//    return 0;
//}
//#include <signal.h>
//#include <ncurses.h>
//
//void sigwinch_handler(int sig) {
//    // Resize the terminal to the new size
//	endwin();
//	refresh();
//    resize_term(LINES, COLS);
//}
//
//int main() {
//    // Initialize ncurses
//    initscr();
//    cbreak();
//    noecho();
//
//    // Register the SIGWINCH signal handler
//    signal(SIGWINCH, sigwinch_handler);
//
//    // Print the initial size of the screen
//    printw("Initial screen size: %d rows, %d columns\n", LINES, COLS);
//
//    // Wait for user input
//    refresh();
//    getch();
//
//    // Resize the screen
//    resize_term(40, 80);
//
//    // Print the new size of the screen
//    printw("New screen size: %d rows, %d columns\n", LINES, COLS);
//
//    // Wait for user input
//    refresh();
//    getch();
//
//    // Clean up and exit
//    endwin();
//    return 0;
//}
