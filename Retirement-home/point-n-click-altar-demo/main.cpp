// @BAKE g++ -o $*.out $@ -lraylib -ggdb
#include <vector>
#include <list>
#include <string>
#include <variant>
#include <raylib.h>
#include "DeferredErase.hpp"
#include "resource_manager.hpp"
#include "dyrect.h"
#include "dictate.hpp"

using namespace std;

bool is_developer_mode =
#ifdef DEBUG
    true
#else
    false
#endif
;

const int W = 1920;
const int H = 1080;
resource_manager<Texture2D> * rms;
resource_manager<Sound> * arm;

namespace player { // XXX
    void say(const char * s);
    void indicate(void);
}

#include "Entity.hpp"
#include "Command.hpp"
#include "State_machine.hpp"

Cursor_command cc;
Command_queue cq;

#include "Actor.hpp"
#include "Background_managment_system.hpp"
#include "Actor_management_system.hpp"
#include "Item_management_system.hpp"
#include "Effect_management_system.hpp"

Background_managment_system bms;
Actor_management_system ams;
Effect_management_system ems;

void player::say(const char * s) {
    ems.main_bouble.text = s;
    ems.main_bouble.text_creation = GetTime();
}

void player::indicate(void) {
    ems.is_indicating = true;
}

namespace player {
    Item_management_system ims;
};

vector<Entity*> entities;

int main(void) {
    InitWindow(W, H, "The Altar");
    InitAudioDevice();

    rms = new resource_manager<Texture2D>(
        LoadTexture,
        +[](Texture2D t) -> bool {
            return !(t.id == 0);
        },
        UnloadTexture
    );
    arm = new resource_manager<Sound>(
        LoadSound,
        +[](Sound s) -> bool {
            return !(s.frameCount == 0);
        },
        UnloadSound
    );

    HideCursor();
    SetTargetFPS(60);

    player::ims.non_owned_items.emplace_back(
        "candle",
        rms->get("asset/candles.png"),
        Vector2 {441, 245},
        "A bunch of candles."
    );

    player::ims.non_owned_items.emplace_back(
        "paint",
        rms->get("asset/paint.png"),
        Vector2 {89, 201},
        "A bucket of \"red paint\"."
    );

    player::ims.non_owned_items.emplace_back(
        "match",
        rms->get("asset/matches.png"),
        Vector2 {192, 954},
        "Matches."
    );

    enum {
        INITIAL,
        PAINTED,
        CANDLED,
        PAINTED_AND_CANDLED,
        LIT,
        ALTAR_STATES_END,
    };

    auto & altar = ams.actors.emplace_back(
        Rectangle {654, 704, 800, 300},
        "I'll build my altar here.",
        ALTAR_STATES_END
    );

    altar.st.set_handler(INITIAL, "paint", HANDLER {
        self->is_visible = true;
        self->texture = rms->get("asset/pentagram.png");
        cq.issue_command({"erase-hand"});
        PlaySound(arm->get("asset/click.mp3"));
        return PAINTED;
    });

    altar.st.set_handler(INITIAL, "candle", HANDLER {
        self->is_visible = true;
        self->texture = rms->get("asset/candle_circle.png");
        cq.issue_command({"erase-hand"});
        PlaySound(arm->get("asset/click.mp3"));
        return CANDLED;
    });

    altar.st.set_handler(PAINTED, "candle", HANDLER {
        self->texture = rms->get("asset/candle_pentagram.png");
        cq.issue_command({"erase-hand"});
        PlaySound(arm->get("asset/click.mp3"));
        return PAINTED_AND_CANDLED;
    });

    altar.st.set_handler(CANDLED, "paint", HANDLER {
        self->texture = rms->get("asset/candle_pentagram.png");
        self->description = "Soon...";
        cq.issue_command({"erase-hand"});
        PlaySound(arm->get("asset/click.mp3"));
        return PAINTED_AND_CANDLED;
    });

    altar.st.set_handler(PAINTED_AND_CANDLED, "match", HANDLER {
        cq.issue_command({"screamer"});
        cq.issue_command({"erase-hand"});
        return LIT;
    });

    entities.push_back(&bms);
    entities.push_back(&player::ims);
    entities.push_back(&ams);
    entities.push_back(&ems);
    entities.push_back(&cq);

    while (!WindowShouldClose()) {
        // Input
        if (IsKeyDown(KEY_LEFT_CONTROL)
        &&  IsKeyPressed(KEY_D)) {
            is_developer_mode = !is_developer_mode;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            cc.name = "take";
        } else
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            cc.name = "inspect";
        } else {
            cc.name = "hover";
        }
        cc.position = {(float)GetMouseX(), (float)GetMouseY()};

        // Update
        for (auto & i : entities) {
            i->update();
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (auto & i : entities) {
            i->draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
