#include "all.h"

void game_frame(game_t * game, size_t frame, float x, float y) {
  game->frame_x[frame] = x;
  game->frame_y[frame] = y;
}

Vector2 game_frame_vector(game_t * game, size_t frame) {
  return (Vector2) { game->frame_x[frame], game->frame_y[frame]};
}
