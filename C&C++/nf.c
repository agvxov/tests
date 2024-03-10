#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>

void* fool(void* args){
	sleep(2);
    ungetch('x');
    ungetch('c');
    printw(" OK");
	refresh();
}

int main() {
    initscr();
    cbreak(); // Set cbreak mode on

    printw("Press any key to continue...");
    refresh();

	pthread_t th;
	pthread_create(&th, NULL, fool, NULL);

    getch();
	pthread_join(th, NULL);

    endwin();
    return 0;
}
