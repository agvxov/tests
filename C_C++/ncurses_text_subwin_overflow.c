// @BAKE gcc $@ -o $*.out $(pkg-config --libs ncurses)
#include <ncurses.h>
#include <string.h>

const char *long_msg = "The dull BONG of metal against a face followed by a pained ‘NYAAAH!’ tell you all you need to know! As Tzah-Tzie tumbles onto the dock like a bag of groceries, you give the air her head previously occupied a good SMACK with your hand and send a heavy, metal barrel cover clattering to the floor!";

int main() {
    WINDOW *mainwin, *subwin;

    // Initialize ncurses
    initscr();
    noecho();
    cbreak();

    // Create the main window
    int height = 20, width = 40, starty = 2, startx = 4;
    mainwin = newwin(height, width, starty, startx);

    refresh();

    box(mainwin, 0, 0);  // Add a border to the main window
    mvwprintw(mainwin, 0, 1, "Main Window");

    // Create a subwindow: narrow but tall
    int sub_height = height - 4, sub_width = 15;
    int sub_starty = starty + 2, sub_startx = startx + 2;
    subwin = derwin(mainwin, sub_height, sub_width, 2, 2);
    box(subwin, 0, 0);  // Add a border to the subwindow
    mvwprintw(subwin, 0, 1, "Subwin");

    // Print the message into the subwindow
    mvwprintw(subwin, 1, 1, "%s", long_msg);

    // Refresh both windows
    wrefresh(mainwin);
    wrefresh(subwin);
    refresh();

    // Wait for input before closing
    getch();

    // Clean up and end ncurses
    delwin(subwin);
    delwin(mainwin);
    endwin();

    return 0;
}
