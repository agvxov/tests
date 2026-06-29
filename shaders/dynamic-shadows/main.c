// @BAKE gcc -o $*.out $@ -lraylib -std=c23 -Wall -Wpedantic -ggdb
#include "raylib.h"

const int W = 800;
const int H = 600;

Rectangle light_rect;
Vector2 light_pos;

Rectangle obelisk_rect = {
    W - 250,
    H - 250,
    80,
    80,
};

Vector4 obelisk_rect_a = {
    W - 250,
    H - 250,
    80,
    80,
};

void set_light_pos(float x, float y) {
    light_rect.x = x - light_rect.width / 2;
    light_rect.y = y - light_rect.height / 2;

    light_pos = (Vector2) {
        .x = light_rect.x + light_rect.width  / 2,
        .y = light_rect.y + light_rect.height / 2,
    };
}

int main(void) {
    InitWindow(W, H, "Raylib - Hello World");
    SetTargetFPS(60);
    HideCursor();

    light_rect.width  = 20;
    light_rect.height = 20;

    float radius = 600;

    set_light_pos(W/2, H/2);

    // ---
    RenderTexture2D buffer_texture = LoadRenderTexture(W, H);

    Shader shader = LoadShader(nullptr, "main.fs");
    SetShaderValue(
        shader,
        GetShaderLocation(shader, "W"),
        &W,
        SHADER_UNIFORM_INT
    );
    SetShaderValue(
        shader,
        GetShaderLocation(shader, "H"),
        &H,
        SHADER_UNIFORM_INT
    );

    SetShaderValue(
        shader,
        GetShaderLocation(shader, "u_radius"),
        &radius,
        SHADER_UNIFORM_FLOAT
    );

    SetShaderValue(
        shader,
        GetShaderLocation(shader, "u_obelisk"),
        &obelisk_rect_a,
        SHADER_UNIFORM_VEC4
    );

    while (!WindowShouldClose()) {
        // Input
        if (IsCursorOnScreen()) {
            set_light_pos(
                GetMouseX(),
                GetMouseY()
            );
        }

        // Drawing
        SetShaderValue(
            shader,
            GetShaderLocation(shader, "u_light_pos"),
            &light_pos,
            SHADER_UNIFORM_VEC2
        );

        BeginTextureMode(buffer_texture);
            ClearBackground(WHITE);
            DrawRectangleRec(
                light_rect,
                YELLOW
            );
            DrawRectangleRec(
                obelisk_rect,
                GRAY
            );
        EndTextureMode();

        BeginDrawing();
            BeginShaderMode(shader);
                DrawTextureRec(
                    buffer_texture.texture,
                    (Rectangle) {
                        0,
                        0,
                        buffer_texture.texture.width,
                        -buffer_texture.texture.height,
                    },
                    (Vector2) {
                        0,
                        0,
                    },
                    WHITE
                );
            EndShaderMode();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
