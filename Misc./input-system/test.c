// @BAKE g++ -o $*.out input-system-logical.cpp input-system-backend-raylib.cpp $@ -std=c++20 -Wall -Wpedantic -lraylib -lchad
#include "input-system.hpp"
#include <raylib.h>
extern "C" {
    #include <chad/ini_file.h>
}

const int W = 600;
const int H = 400;

enum {
    MEOW,
    WOOF,
    MOOO,
    UP,
    LEFT,
    DOWN,
    RIGHT,
};

void read_user_bindings(void) {
    Ini_File *ini = ini_file_parse("bindings.ini", NULL);
    if (!ini) {
        TraceLog(LOG_ERROR, "could not read bindings.ini"); return;
    }

    Ini_Section *section = nullptr;
    for (size_t i = 0; i < ini->sections_size; ++i) {
        if (!strcmp(ini->sections[i].name, "bind")) {
            section = &ini->sections[i];
        }
    }

    if (!section) {
        TraceLog(LOG_ERROR, "bindings.ini: missing [bind] section");
        ini_file_free(ini);
        return;
    }

    for (size_t i = 0; i < section->properties_size; ++i) {
        auto &p = section->properties[i];
        int action = !strcmp(p.key, "MEOW")  ? MEOW  :
                     !strcmp(p.key, "WOOF")  ? WOOF  :
                     !strcmp(p.key, "MOOO")  ? MOOO  :
                     !strcmp(p.key, "UP")    ? UP    :
                     !strcmp(p.key, "LEFT")  ? LEFT  :
                     !strcmp(p.key, "DOWN")  ? DOWN  :
                     !strcmp(p.key, "RIGHT") ? RIGHT : -1
        ;

        if (action < 0) {
            TraceLog(LOG_ERROR, "unknown binding: %s", p.key);
            continue;
        }

        bind(parse_hotkey(p.value), action);
        const char * error = get_input_system_error();
        if (*error != '\0') { TraceLog(LOG_ERROR, "%s", error); }
    }

    ini_file_free(ini);
}

signed main(void) {
    bind(parse_hotkey("shift + a"), MEOW);
    bind(parse_hotkey("shift + w"), WOOF);
    bind(parse_hotkey("shift + d"), MOOO);
    bind(parse_hotkey("w"), UP);
    bind(parse_hotkey("a"), LEFT);
    bind(parse_hotkey("s"), DOWN);
    bind(parse_hotkey("d"), RIGHT);

    read_user_bindings();

    InitWindow(W, H, "Input prototype");
    SetTargetFPS(60);

    Vector2 p{W / 2.0f, H / 2.0f};
    const char * sound = "";

    TraceLog(LOG_INFO, stringify_hotkey(parse_hotkey("ctrl + g")));

    while (!WindowShouldClose()) {
        read_input();

        p.x += is_down(RIGHT) * 2 - is_down(LEFT) * 2;
        p.y += is_down(DOWN)  * 2 - is_down(UP)   * 2;

        if (is_pressed(MEOW)) { sound = "MEOW"; }
        if (is_pressed(WOOF)) { sound = "WOOF"; }
        if (is_pressed(MOOO)) { sound = "MOOO"; }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawCircleV(p, 20, RED);
            DrawText(sound, W - MeasureText(sound, 20) - 10, 10, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
}
