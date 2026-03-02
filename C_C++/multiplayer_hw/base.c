// @BAKE gcc -o $*.out $@ -lraylib -std=c23 -Wall -Wpedantic -ggdb
#include "raylib.h"

const int W = 600;
const int H = 400;

typedef struct {
    float x;
    float y;
} player_t;

player_t player1;

void control_player(void) {
    const float step = 8.0f;

    if (IsKeyDown(KEY_W)) { player1.y -= step; }
    if (IsKeyDown(KEY_S)) { player1.y += step; }
    if (IsKeyDown(KEY_A)) { player1.x -= step; }
    if (IsKeyDown(KEY_D)) { player1.x += step; }

    /* screen wrap */
    if (player1.x < 0)  { player1.x += W; }
    if (player1.x >= W) { player1.x -= W; }
    if (player1.y < 0)  { player1.y += H; }
    if (player1.y >= H) { player1.y -= H; }
}

void draw_player(void) {
    DrawCircle(player1.x, player1.y, 10, BLUE);
}

int main(void) {
    InitWindow(W, H, "Raylib - Hello World");
    SetTargetFPS(30);

    player1 = (player_t) {
        .x = 100,
        .y = 100,
    };

    while (!WindowShouldClose()) {
        control_player();

      BeginDrawing();
        ClearBackground(RAYWHITE);
        draw_player();
      EndDrawing();
    }

    CloseWindow();
    return 0;
}
