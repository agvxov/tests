#include "all.h"

void draw_square_grid(game_t * game, size_t frame, int size, Texture * texture, int * array, size_t length) {
  (void)texture;
  float x = game->frame_x[frame], y = game->frame_y[frame];
  float square_length = size;
  size_t square = floor(sqrt(length));
  size_t j, i;
  for (i = 0; i < square; ++i) {
    for (j = 0; j < square; ++j) {
      DrawRectangleV((Vector2){x+i*square_length, y+j*square_length},
		     (Vector2){square_length, square_length},
		     (Color){80+array[(i*square)+(j)]*18, 0, 0, 255});
    }
  }
}

/* void draw_vertical_bargraph(game_t * game, size_t frame, int size, Color color, int * array, size_t length) { */
/* } */

void draw_centered_text(game_t * game, size_t frame, int font_size, Color color, char * format, ...) {
  char buffer[TEXT_BUFFER_LIMIT];
  float x = game->frame_x[frame], y = game->frame_y[frame];
  va_list ap;
  va_start(ap, format);
  vsnprintf(buffer, TEXT_BUFFER_LIMIT, format, ap);
  va_end(ap);
  Vector2 v = MeasureTextEx(game->font, buffer, font_size, 1);
  DrawTextEx(game->font, buffer, (Vector2){x-v.x/2, y-v.y/2}, font_size, 1, color);
}
