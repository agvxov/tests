// @BAKE gcc $@ raygui.o -o $*.out -lraylib -lm -Wall -Wpedantic -ggdb
/* NOTE:
 *  + this program as made to test out raygui
 *  + raygui seems rather fine; its simple and painless
 *  + immediate-mode of course means that there is a violation
 *     of conventional gamedev concerns, where state is modified during drawing,
 *     however this is perfectly acceptable for the utility provided,
 *     just dont write the game state from GUI directly chud (in real games anyways)
 *
 *  file raygui.c {
 *    // @BAKE gcc -c $@ -o $*.o -lraylib -Wall -Wpedantic -ggdb
 *    #define RAYGUI_IMPLEMENTATION
 *    #include "raygui.h"
 *  }
 */
#include <stdlib.h>
#include <raylib.h>
#include "raygui.h"
#include "dyrect.h"

const int W = 1000;
const int H = 800;

#define MAX_PARTICLES 10

typedef struct {
    int x, y;
    int fuse;
    struct explosion {
        int after_burn;
        struct particle {
            float x;
            float y;
            float x_i;
            float y_i;
        } particles[MAX_PARTICLES];
    } explosion;
} firework_t;

bool is_null_firework(firework_t f) {
    return f.x == -1 && f.y == -1;
}

void null_firework(firework_t * f) {
    f->x = -1;
    f->y = -1;
}

#define MAX_FIREWORKS 50
#define foreach_firework for (int i = 0; i < MAX_FIREWORKS; i++)
firework_t fireworks[MAX_FIREWORKS];

/* Interactive Config */
bool is_config_visible = true;
int speed              = 1;
int fuse_time_min      = 180;
int fuse_time_entropy  = 40;
int after_burn_time    = 30;
int particle_max_i     = 5;
Color firework_color   = BLACK;
Color particle_color   = RED;
/* --- */

void random_init_firework(firework_t * f) {
    *f = (firework_t) {
        .x = rand() % W,
        .y = H + (rand() % 100),
        .fuse = fuse_time_min + (rand() % fuse_time_entropy),
        .explosion = (struct explosion) {
            .after_burn = after_burn_time,
        },
    };

    for (int i = 0; i < MAX_PARTICLES; i++) {
        (*f).explosion.particles[i] = (struct particle) {
            .x   = -1,
            .y   = -1,
            .x_i = (rand() % (particle_max_i*2)) - particle_max_i,
            .y_i = (rand() % (particle_max_i*2)) - particle_max_i,
        };
    }
}

void blow_firework(firework_t * f) {
    if (f->explosion.after_burn == 0) {
        null_firework(f);
        return;
    }

    if (f->explosion.after_burn == after_burn_time) {
        for (int i = 0; i < MAX_PARTICLES; i++) {
            struct particle * p = f->explosion.particles + i;
            p->x += f->x;
            p->y += f->y;
        }
    } else {
        for (int i = 0; i < MAX_PARTICLES; i++) {
            struct particle * p = f->explosion.particles + i;
            p->x += p->x_i;
            p->y += p->y_i;
        }
    }
    
    --f->explosion.after_burn;
}

void update_fireworks(void) {
    foreach_firework {
        firework_t * f = fireworks + i;

        if (is_null_firework(*f)) {
            random_init_firework(f);
        }

        if (f->fuse == 0) {
            blow_firework(f);
        } else {
            f->y -= speed;
            --f->fuse;
        }
    }
}

void draw_fireworks(void) {
    foreach_firework {
        const firework_t f = fireworks[i];
        if (is_null_firework(f)) { continue; }

        if (f.fuse > 0) {
            DrawRectangle(
                f.x,
                f.y,
                4,
                18,
                firework_color
            );
        } else {
            for (int i = 0; i < MAX_PARTICLES; i++) {
                DrawRectangle(
                    f.explosion.particles[i].x,
                    f.explosion.particles[i].y,
                    5,
                    5,
                    particle_color
                );
            }
        }
    }
}

void do_gui(void) {
    bool toggle_settings = GuiButton(
        (Rectangle) {
            10,
            10,
            24,
            24,
        },
        GuiIconText(ICON_GEAR, NULL)
    );

    if (toggle_settings) {
        is_config_visible = !is_config_visible;
    }

    if (is_config_visible == false) { return; }

    // --

    Rectangle menu_box = (Rectangle) {
        W - 310,
        10,
        300,
        H - 20,
    };

    toggle_settings = GuiWindowBox(
        menu_box,
        "Settings"
    );
    if (toggle_settings) {
        is_config_visible = !is_config_visible;
        return;
    }

    // --

    Rectangle menu_item_box = (Rectangle) {
        menu_box.x + 20,
        menu_box.y + 30,
        100,
        30,
    };

    do {
        Rectangle particle_label_box = menu_item_box;

        GuiLabel(particle_label_box, "Particle Color:");

        Rectangle particle_colorpicker_box = after(particle_label_box, 1);
        particle_colorpicker_box.height = particle_colorpicker_box.width;

        GuiColorPicker(
            particle_colorpicker_box,
            "fag",
            &particle_color
        );
    } while (0);

    do {
        Rectangle projectile_label_box = next(menu_item_box, 1);
        projectile_label_box.x += 40;

        GuiLabel(projectile_label_box, "Projectile Color:");

        Rectangle projectile_colorpicker_box = after(projectile_label_box, 1);
        projectile_colorpicker_box.height = projectile_colorpicker_box.width;

        GuiColorPicker(
            projectile_colorpicker_box,
            "fag",
            &firework_color
        );
    } while (0);

    do {
        menu_item_box.y += 150;

        Rectangle fuse_time_min_label_box = menu_item_box;

        GuiLabel(
            fuse_time_min_label_box,
            TextFormat("Min fuse time (%d):",
                fuse_time_min
            )
        );

        Rectangle fuse_time_min_slider_box = fuse_time_min_label_box;
        fuse_time_min_slider_box.y += 20;
        fuse_time_min_slider_box.width = 240;
        fuse_time_min_slider_box.height = 20;

        float f = fuse_time_min;
        GuiSlider(
            fuse_time_min_slider_box,
            "0",
            "600",
            &f,
            0,
            600
        );
        fuse_time_min = (int)f;
    } while (0);

    do {
        menu_item_box.y += 40;

        Rectangle fuse_time_entropy_label_box = menu_item_box;

        GuiLabel(
            fuse_time_entropy_label_box,
            TextFormat("Fuse entropy (%d):",
                fuse_time_entropy
            )
        );

        Rectangle fuse_time_entropy_slider_box = fuse_time_entropy_label_box;
        fuse_time_entropy_slider_box.y += 20;
        fuse_time_entropy_slider_box.width = 240;
        fuse_time_entropy_slider_box.height = 20;

        float f = fuse_time_entropy;
        GuiSlider(
            fuse_time_entropy_slider_box,
            "30",
            "150",
            &f,
            30,
            150
        );
        fuse_time_entropy = (int)f;
    } while (0);

    do {
        menu_item_box.y += 40;

        Rectangle speed_label_box = menu_item_box;

        GuiLabel(
            speed_label_box,
            TextFormat("Speed (%d):",
                speed
            )
        );

        Rectangle speed_slider_box = speed_label_box;
        speed_slider_box.y += 20;
        speed_slider_box.width = 240;
        speed_slider_box.height = 20;

        float f = speed;
        GuiSlider(
            speed_slider_box,
            "1",
            "30",
            &f,
            1,
            30
        );
        speed = (int)f;
    } while (0);
}

int main(void) {
    srand(0);
    InitWindow(W, H, "RayGUI test - Fireworks");

    SetTargetFPS(60);

    foreach_firework {
        null_firework(fireworks + i);
    }

    while (!WindowShouldClose()) {
        update_fireworks();

      BeginDrawing();
        ClearBackground(RAYWHITE);
        draw_fireworks();
        do_gui();
      EndDrawing();
    }

    CloseWindow();
    return 0;
}
