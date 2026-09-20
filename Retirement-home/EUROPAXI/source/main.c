#include <time.h>
#include <unistd.h>
#include <rlgl.h>

#include "all.h"

/* I really like this in usage. */

static inline void frame_reset(game_t * game) {
  game_frame(game, 0, game->horizontal/12, game->vertical/12);
  game_frame(game, 1, game->horizontal/3, game->vertical - game->vertical/8);
  game_frame(game, 2, game->horizontal - game->horizontal/4, game->vertical/12);
}

int main (int count, char ** arguments)
{
  (void)count;
  game_t game[1] = {0};
  game->horizontal = 1920;
  game->vertical = 1080;
  /* :config */
  frame_reset(game);
  { /* this idented (DENTED) style is autistic and dumb but I like it visually */
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    /* tell raylib to shut up */
    /* SetTraceLogLevel(LOG_NONE); */
    InitWindow(game->horizontal, game->vertical, arguments[0]);
    SetWindowState(FLAG_WINDOW_HIDDEN);
    InitAudioDevice();
    SetWindowPosition(0, 0);
  }
  game->font = LoadFont("fonts/Atkinson/mono/AtkinsonHyperlegibleMono-Bold.otf");
  if (!IsFontValid(game->font)) { game->font = GetFontDefault(); }

    /* :todo ping me I'll update this to a u/f seperated game loop */
  { /* loop to end all loops */
    uint64_t fc = 0;
    /* :config */
    float    fps = 30;
    double   wait = wait = 1.0 / fps, delta = wait;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    ClearWindowState(FLAG_WINDOW_HIDDEN);
    int test[200*200] = {0};
    for (int i = 0; i < 200*200; i++) { test[i] = i;}
    while (1) {
      if (delta > wait) {
	clock_gettime(CLOCK_MONOTONIC, &start);
        { /* update */
	  ++fc;
	  PollInputEvents();
	  if (IsWindowResized()) {
	    game->horizontal = GetScreenWidth(), game->vertical = GetScreenHeight();
	    frame_reset(game);
	  }
	  /* physical keys */
	  switch (GetKeyPressed()) {
	    /* case KEY_Q: goto stop; */
	    case KEY_ESCAPE: goto stop;
	  }
	  /* routed keys */
	  /* switch (GetCharPressed()) { case 'q': goto stop; } */
	}
	{ /* draw */
	  BeginDrawing();
	  ClearBackground(BLACK);
	  draw_square_grid(game, 0, MIN(game->vertical/20, game->horizontal/25), NULL, test, 200);
	  draw_centered_text(game, 1, 20, WHITE, "Snails are now preparing!");
	  draw_centered_text(game, 2, 20, WHITE, "Gambling here");
	  rlDrawRenderBatchActive();
	  SwapScreenBuffer();
	}
      }
      clock_gettime(CLOCK_MONOTONIC, &end);
      delta = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
      if (delta < wait) {
	double should = -(delta - wait);
	if (should > 0) { usleep(1e6 * should); }
      }
    }
  }
stop:
  SetWindowState(FLAG_WINDOW_HIDDEN);
  UnloadFont(game->font);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
