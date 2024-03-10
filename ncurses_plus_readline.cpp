// @COMPILECMD g++ $@ $(pkg-config --libs ncurses readline)
#include <ncurses.h>
#include <readline/readline.h>

#define WINDOW_WIDTH 32
#define WINDOW_HEIGHT 3

int scr_h, scr_w;
WINDOW* myWindow;

int input_available = false;	// C style bool to track when to stop reading
char input;						// our input; since we read char-by-char this is all the buffering we need

inline void init(){
	// Ncurses (nothing special)
	initscr();
	noecho();
	curs_set(0);

	getmaxyx(stdscr, scr_h, scr_w);
	myWindow = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, 
			( scr_h / 2 ) - 1, ( scr_w - WINDOW_WIDTH) / 2);
	refresh();

	box(myWindow, 0, 0);
	// Readline
	//   make readline shut up
	rl_bind_key('\t', rl_insert);	// make tab insert itself
	rl_catch_signals = 0;			// do not install signal handlers
	rl_catch_sigwinch = 0;			// do not care about window change signals
	rl_prep_term_function = NULL;	// do not initialize the ternimal
	rl_deprep_term_function = NULL; // do not clean up
	rl_change_environment = 0;		// ?!
	//   bind callbacks, for seemless integration
	rl_getc_function = +[](FILE* ignore){	// define how Readline is handed chars
		input_available = false; // since we read 1 char at the time we know that there will be no more available
		return (int)input;
	};
	rl_input_available_hook = +[]{	// let Readline know that it shall call it rl_getc_function
		return input_available;
	};
	rl_redisplay_function = +[]{	// instruct Readline what to do after rl_line_buffer has changed
		// echo rl_line_buffer (without using the terminals built in echo)
		wmove(myWindow, 1, 1);
		wclrtoeol(myWindow);
		box(myWindow, 0, 0);	// wclrtoeol(), screws with the box
		waddstr(myWindow, rl_line_buffer);
		wrefresh(myWindow);
		return;
	};
	rl_callback_handler_install("", +[](char *line){	// instruct Readline what to do once rl_line_buffer is submitted (enter hit)
		// print the submitted line to the top of the screen
		wmove(stdscr, 0, 0);
		wclrtoeol(stdscr);
		waddstr(stdscr, line);
		wrefresh(stdscr);
		return;
	});
}

signed main(){
	init();
	wrefresh(myWindow);

	while(1){
		input = wgetch(myWindow);
		input_available = true;
		rl_callback_read_char();
	}
}
