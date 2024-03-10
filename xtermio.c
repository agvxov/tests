#include <stdio.h>
#include <termio.h>
#include <string.h>
#include <unistd.h>

/*
 @COMPILECMD clang -g -ansi -Weverything -o gaem $@
   valgrind --show-leak-kinds=all --leak-check=full ./gaem
*/

#define WIDTH  (80)
#define HEIGHT (24)

enum {
	EFFECT_NORMAL,
	EFFECT_BOLD,
	EFFECT_DARK,
	EFFECT_ITALIC,
	EFFECT_UNDERLINE,
	EFFECT_BLINK,
	EFFECT_UNDEFINED,
	EFFECT_REVERSE
};

enum {
	COLOUR_GREY,
	COLOUR_RED,
	COLOUR_GREEN,
	COLOUR_YELLOW,
	COLOUR_BLUE,
	COLOUR_PINK,
	COLOUR_CYAN,
	COLOUR_WHITE
};

static char screen [12 * WIDTH * HEIGHT + (HEIGHT - 1) * 2 + 4] = "\033[H";

static int player [2] = { 0, 0 };

static struct termios old_terminal;
static struct termios new_terminal;

static void render_character (
	char character,
	int  x,
	int  y,
	int  effect,
	int  colour
) {
	char format [13] = "\033[ ;3 m \033[0m";

	format [2] = (char) effect + '0';
	format [5] = (char) colour + '0';
	format [7] = character;

	memcpy (& screen [12 * (WIDTH * y + x) + y * 2 + 3], & format [0], sizeof (format) - 1);
}

static void player_move (int direction, int step) {
	player [(int) (direction != 0)] += step;

	if (player [0] > WIDTH  - 1) { player [0] = WIDTH  - 1; }
	if (player [0] <          0) { player [0] =          0; }
	if (player [1] > HEIGHT - 1) { player [1] = HEIGHT - 1; }
	if (player [1] <          0) { player [1] =          0; }
}

int main (
	int      argc,
	char * * argv
) {
	char signal = '\0';
	int  offset = 0;

	(void) argc;
	(void) argv;

	tcgetattr (STDIN_FILENO, & old_terminal);

	new_terminal = old_terminal;

	new_terminal.c_cc [VMIN]  = (unsigned char) 0;
	new_terminal.c_cc [VTIME] = (unsigned char) 1;

	new_terminal.c_iflag &= (unsigned int) ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	new_terminal.c_oflag &= (unsigned int) ~(OPOST);
	new_terminal.c_cflag |= (unsigned int)  (CS8);
	new_terminal.c_lflag &= (unsigned int) ~(ECHO | ICANON | IEXTEN | ISIG);

	tcsetattr (STDIN_FILENO, TCSAFLUSH, & new_terminal);

	for (offset = 0; offset != HEIGHT - 1; ++offset) {
		memcpy (& screen [12 * WIDTH * (offset + 1) + offset * 2 + 3], "\r\n", sizeof ("\r\n") - 1);
	}

	do {
		signal = '\0';

		for (offset = 0; offset != WIDTH * HEIGHT; ++offset) {
			render_character ('.', offset % WIDTH, offset / WIDTH, EFFECT_BOLD, COLOUR_GREY);
		}

		render_character ('@', player [0], player [1], EFFECT_BOLD, COLOUR_RED);

		(void) write (STDOUT_FILENO, screen, sizeof (screen));

		(void) read (STDIN_FILENO, & signal, sizeof (signal));

		if (signal == 'w') { player_move (1, -1); }
		if (signal == 'a') { player_move (0, -1); }
		if (signal == 's') { player_move (1,  1); }
		if (signal == 'd') { player_move (0,  1); }
	} while (signal != 'Q');

	tcsetattr (STDIN_FILENO, TCSAFLUSH, & old_terminal);

	(void) write (STDOUT_FILENO, "\033[2J\033[H", sizeof ("\033[2J\033[H"));

	return (0);
}

