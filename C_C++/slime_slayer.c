// @BAKE gcc $@ -o $*.out -g
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>

#define MAP_SIZE 9
#define INIT_CURSOR    fputs("\033[?25l\n\033[s", stdout)
#define RESTORE_CURSOR fputs("\033[u", stdout) 
#define CLEAR_LINE      puts("\033[K");
#define PUT_PROP(y, x, c) do { \
    RESTORE_CURSOR; fputs("\033[1B", stdout); \
    char move_cursor[] = "\033[#G\033[#B"; \
    move_cursor[2] = x+'1'; \
    move_cursor[6] = y+'1'; \
    fputs(move_cursor, stdout); \
    putchar(c); \
} while (0)
#define MAKE_RULER for (int i = 0; i < MAP_SIZE; i++) { putchar('-'); }; puts("");

struct enemy_t {
    int is_alive, health, power, x, y;
} * enemies;

int ticks = 0, is_level_over = 1, level = 1, x = 5, y = 5, health = 100;
unsigned power = 1;
struct termios myterm, oldterm;

signed main() {
    void my_exit([[maybe_unused]] int ignore) {
        PUT_PROP(8, 1, ' ');
        fputs("You died!\n\033[?25h", stdout);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
        exit(0);
    }
    signal(SIGINT, my_exit);
    srand((int)(long)&main);
    INIT_CURSOR;

    tcgetattr(STDIN_FILENO, &oldterm);
    myterm = oldterm;
    myterm.c_lflag &= ~(ICANON | ECHO);
    myterm.c_cc[VMIN] = 1;
    myterm.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &myterm);

    enemies = calloc(10, sizeof(struct enemy_t));

    do {
        is_level_over = 1;
        RESTORE_CURSOR;
        CLEAR_LINE;

        MAKE_RULER;
        for (int i = 0; i < MAP_SIZE; i++) { CLEAR_LINE; }
        MAKE_RULER;

        PUT_PROP(y, x, '@');
        for (int i = 0; i < MAP_SIZE; i++) {
            if (!enemies[i].is_alive) { continue; }
            is_level_over = 0;
            PUT_PROP(enemies[i].y, enemies[i].x, '#');
            if (abs(x - enemies[i].x) < 2
            &&  abs(y - enemies[i].y) < 2) {
                health -= enemies[i].power;
                enemies[i].health -= power;
                if (enemies[i].health < 0) {
                    enemies[i].is_alive = 0;
                    switch(rand() % 2) {
                        case 0: power  += enemies[i].power;
                        case 1: health += 10;
                    }
                }
            } else {
                enemies[i].x += (x == enemies[i].x ? 0 : (x > enemies[i].x ? 1 : -1));
                enemies[i].y += (y == enemies[i].y ? 0 : (y > enemies[i].y ? 1 : -1));
            }
        }

        if (is_level_over) {
            ++level;
            const int n_enemies = (rand() % MAP_SIZE+1);
            for (int i = 0; i < n_enemies; i++) {
                enemies[i].is_alive = 1;
                enemies[i].health = (rand() % (int)(level * 1.5)) + 1;
                enemies[i].power  = (rand() % (int)(level * 1.5)) + 1;
                enemies[i].x      = (rand() % MAP_SIZE) + 1;
                enemies[i].y      = (rand() % MAP_SIZE) + 1;
            }
        }

        RESTORE_CURSOR;
        printf("Level: %-5d Health: %-5d Power: %-5d\n", level, health, power);

        switch (getchar()) {
            case 'h': if (x > 0)          { --x; } break;
            case 'l': if (x < MAP_SIZE-1) { ++x; } break;
            case 'k': if (y > 0)          { --y; } break;
            case 'j': if (y < MAP_SIZE-1) { ++y; } break;
        }
        if (!(ticks++ % 10)) { health += 2; }
    } while (health > 0);
    my_exit(0);
}
