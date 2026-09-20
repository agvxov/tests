#include "raylib.h"
#include "box2d/box2d.h"
#include "chad.h"

#include "world.h"

int main (int count, char ** arguments) {
  char * window_name = arguments[0];
  while (++arguments, --count > 0) {
    while (**arguments == '-') { ++*arguments; }
    struct options * option = options_lookup(*arguments,strlen(*arguments));
    if (!option) {
      printf("Unknown option '%s', try 'help'\n", *arguments);
      return 1;
    }
    switch (option->number) {
    case OPTION_HELP: {
      dictate("Nobody can help you now!\n");
      exit(0); }
    }
  }

    const int W = 1200;
    const int H = 1200;

    InitWindow(W, H, window_name);
    SetTargetFPS(60);

    draw_context_t my_draw_context = (draw_context_t) {
        .world_offset = (Vector2) {
           -300,
           -450,
        },
        .scale = 1.3f,
    };

    b2WorldId world = CreateMortalWorld();

    RenderTexture2D screen_pip = LoadRenderTexture(900, 900);

    while (!WindowShouldClose()) {

        // Drawing
        /* NOTE: I'm experimenting with the for thing,
         *        what do you think?
         *       Do you think it should be wrapped with a macro?
         *       that would mean COMA is legally required tho
         */
        for (
          int i = (BeginTextureMode(screen_pip), 0);
          i == 0;
          EndTextureMode(), i++
        ) {
            DrawWorld(world, my_draw_context);
        }

        for (
          int i = (BeginDrawing(), 0);
          i == 0;
          EndDrawing(), i++
        ) {
            ClearBackground(RAYWHITE);
            DrawTextureRec(
                screen_pip.texture,
                (Rectangle) {
                    0,
                    0,
                    screen_pip.texture.width,
                    screen_pip.texture.height,
                },
                (Vector2) {
                    30,
                    30,
                },
                WHITE
            );
        }
    }

    CloseWindow();
    return 0;
}
