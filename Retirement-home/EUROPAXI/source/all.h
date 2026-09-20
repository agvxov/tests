#ifndef EVERYTHING_ALWAYS_H_
#define EVERYTHING_ALWAYS_H_

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <raylib.h>

#define TEXT_BUFFER_LIMIT (1<<12)
#define FRAME_LIMIT (1<<4)

#define MIN(a,b) (a)<(b)?(a):(b)

typedef struct {
  Font font;
  float frame_x[FRAME_LIMIT];
  float frame_y[FRAME_LIMIT];
  int horizontal, vertical;
} game_t;

/* render.c */

/* Everything here assumes White On Black = OK. for now. */
/* Things should be textured and have backgrounds which is a lot of extra params,
   which are not important right now. */

/* I would prefer that things remain CENTERED as that makes preportional to WINDOW SIZE shit easier */
/*  The Window is resizable, by the way. */

void draw_square_grid		(game_t * game, size_t frame, int size, Texture * texture, int * array, size_t length);
void draw_vertical_bargraph	(game_t * game, size_t frame, int size, Color color, int * arr, size_t length);
void draw_centered_text		(game_t * game, size_t frame, int font_size, Color color, char * format, ...);

/* game.c */

void game_frame(game_t * game, size_t frame, float x, float y);
Vector2 game_frame_vector(game_t * game, size_t frame);

/* ... */

#endif /* EVERYTHING_ALWAYS_H_ */
