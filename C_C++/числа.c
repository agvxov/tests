// @BAKE gcc $@ -o $*.out -std=c2x $(pkg-config --cflags --libs readline)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>

#define N_NUMBERS 101

#define ON_TEEN "на" "дцать"

char * numbers[N_NUMBERS] = {
    [0] = "ноль",
    [1] = "один",
    [2] = "два",
    [3] = "три",
    [4] = "четырe",
    [5] = "пять",
    [6] = "шесть",
    [7] = "семь",
    [8] = "восемь",
    [9] = "девять",

    [11] = "один"   ON_TEEN,
    [12] = "две"    ON_TEEN,
    [13] = "три"    ON_TEEN,
    [14] = "четыр"  ON_TEEN,
    [15] = "пят"    ON_TEEN,
    [16] = "шест"   ON_TEEN,
    [17] = "сем"    ON_TEEN,
    [18] = "восем"  ON_TEEN,
    [19] = "девят"  ON_TEEN,

    [10] = "двадцать",
    [20] = "двадцать",
    [30] = "тридцать",
    [40] = "сорок",
    [50] = "пятьдецят",
    [60] = "шестьдесят",
    [70] = "cемьдесят",
    [80] = "восемьдесят",
    [90] = "девяносто",

    [100] = "сто",
};

void init(void) {
    for (int i = 21; i < 100; i++) {
        if (i % 10 == 0) { continue; }
        asprintf(numbers+i, "%s %s", numbers[(i/10)*10], numbers[i % 10]);
    }
}

signed main(void) {
    init();

  #if 0
    for (int i = 0; i < N_NUMBERS; i++) {
        puts(numbers[i]);
    }
    return 0;
  #endif

    srand((long)&main);
    char * input;
    int a, b, c;

    while (true) {
        a = rand() % N_NUMBERS;
        b = rand() % N_NUMBERS;
        c = a + b;
        c = (c > 100 ? c - 100 : c);

        printf("%s + %s?\n", numbers[a], numbers[b]);

      input:
        input = readline("|отвечать> ");
        if (input == NULL) { break; }

        if (strcmp(input, numbers[c])) {
            puts("Нет!");
            printf("%d + %d = %d\n", a, b, c);
            puts(numbers[c]);
            goto input;
        }

        puts("Да!");
    }
}
