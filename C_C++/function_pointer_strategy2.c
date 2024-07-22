/* @BAKE gcc $@ -o $*.out $(pkg-config --cflags --libs ncurses) -Wpedantic && ./$*.out
 */
#include <stdio.h>

typedef struct {
    const char * description;
    void (*hook)();
} action_t;

typedef struct {
    const char * name;
    action_t * action;
} menu_item_t;

void yellow_line();
void tri_force();
void swap_with_first(menu_item_t * i);
void swap_with_first(move_up);

menu_item_t * menu_items[] = {
    &(menu_item_t){"Item 1", &(action_t){"Print yellow line", yellow_line}},
    &(menu_item_t){"Item 2", &(action_t){"Triforce like and oldfag", tri_force}},
    &(menu_item_t){"Item 3", &(action_t){"Swap with first.", swap_with_first}},
    &(menu_item_t){"Item 4", &(action_t){"Move up", move_up}},
    &(menu_item_t){"Item 5", &(action_t){"print yellow line", yellow_line}},
    &(menu_item_t){"Item 6", &(action_t){"print yellow line", yellow_line}},
    &(menu_item_t){"Item 7", &(action_t){"print yellow line", yellow_line}},
    &(menu_item_t){"Item 8", &(action_t){"print yellow line", yellow_line}},
    &(menu_item_t){"Item 9", &(action_t){"print yellow line", yellow_line}},
};

void action_swap(menu_item_t * a, menu_item_t * b) {
    action_t * swap = a->action;
    a->action = b->action;
    b->action = swap;
}

const unsigned menu_size = sizeof(menu_items) / sizeof(menu_item_t*);

void yellow_line() {
    puts("\033[33m---------\033[0m");
}

void tri_force() {
    puts (
        " ▲ \n"
        "▲ ▲\n"
    );
}

void swap_with_first(menu_item_t * i) {
    action_swap(menu_items[0], i);
}

void move_up(menu_item_t * i) {
    int n = menu_items - i;
    if (n > 1) {
        action_swap(menu_items[n-1], menu_items[n]);
    } else {
        action_swap(menu_items[n], menu_items[menu_size]);
    }
}


void print_menu() {
    for (int i = 0; i < menu_size; i++) {
        printf("%s:\n", menu_items[i]->name);
        printf("  %s\n\n", menu_items[i]->action->description);
    }
    puts("###");
}

signed main() {
    while (1) {
        print_menu();

        char c = getchar();
        while(getchar() != '\n') { ; }

        if (c >= '1'
        &&  c <= ('1' + menu_size)) {
            menu_items[c - '1']->action->hook(menu_items[c - '1']);
        }
    }
}
