// @BAKE gcc -o $*.out linenoise.c $@
#include <stdio.h>
#include "dice.h"
#include "linenoise.h"

// --- COPY PASTE ---
int count_digits(long long n) {
    if (n == 0) { return 1; }

    int count = 0;
    if (n < 0) {
        ++count; // for '-'
        n = -n;
    }

    while (n > 0) {
        n /= 10;
        ++count;
    }

    return count;
}

char * qst_dice(const char * const script, bool parse_only) {
  #define ROLL ((rand() % n_sides) + 1);
    char * r = NULL;

    size_t n_dice;
    size_t n_sides;
    bool   has_modifier = false;
    long   modifier;
    bool   modifier_sign;


    /* Invalid storage is UB.
     * This includes negative input (-1) provided with unsigned variables (size_t).
     * In practice, (GNU) libc will read the input, indicate no error
     *  and creating a wraparound.
     */
    int e = sscanf(script, "dice+%zud%zu+%ld", &n_dice, &n_sides, &modifier);

    if (e != 2
    &&  e != 3) {
        return NULL;
    }

    if (n_dice  == 0
    ||  n_sides == 0) {
        return NULL;
    }

    /* qst_dice() would happily start calculating an absurdly amount of dice rolls.
     * Which is a problem when using it on a server, as it will become a CPU hog
     *  and effectively a DOS.
     * Consequently, this check is provided to restrict the rolls to a sane range.
     * This also means that overflows are impossible (on 64bits).
     */
    if (n_dice  > 1'000
    ||  n_sides > 10'000'000) {
        return NULL;
    }

    if (parse_only) {
        return (char*)0x01;
    }

    size_t max_chars = 0
        + strlen("Rolled ")
        + (n_dice * (count_digits(n_sides) + strlen(", ")))
        + ((count_digits(SIZE_MAX) + strlen(" = ")) * (n_dice > 1))
        + count_digits(n_sides) + count_digits(n_dice) + strlen(" (d)")
        + 1
    ;

    if (e == 3) {
        has_modifier  = true;
        modifier_sign = modifier > 0;
        modifier     *= modifier_sign ? 1 : -1;
        max_chars    += 0
            + (strlen(" + ") + count_digits(modifier)) * 2
        ;
    }

    r = malloc(max_chars);
    if (!r) { return NULL; }
    char * end_ptr = r;

    do {
        memcpy(r, "Rolled ", strlen("Rolled "));
        end_ptr += strlen("Rolled ");
    } while (0);

    do {
        size_t sum = 0;
        size_t roll;

        roll = ROLL;
        end_ptr += sprintf(end_ptr, "%zu", roll);
        sum += roll;

        for (size_t i = 0; i < n_dice-1; i++) {
            roll = ROLL;
            end_ptr += sprintf(end_ptr, ", %zu", roll);
            sum += roll;
        }

        if (n_dice > 1) {
            end_ptr += sprintf(end_ptr, " = %zu", sum);
        }
    } while (0);

    if (has_modifier) {
        end_ptr += sprintf(end_ptr, modifier_sign ? " + %ld" : " - %ld", modifier);
        end_ptr += sprintf(end_ptr, " (%zud%zu %c %ld)",
                    n_dice,
                    n_sides,
                    modifier_sign ? '+' : '-',
                    modifier
        );
    } else {
        end_ptr += sprintf(end_ptr, " (%zud%zu)", n_dice, n_sides);
    }

    return r;
  #undef ROLL
}
// ---

char * dice_hints_callback(const char * line, int * out_color, int * out_bold) {
    if (line[0] == '\0') {
        return NULL;
    }

    if (!qst_dice(line, true)) {
        *out_color = 31;   // ANSI color code (e.g. magenta)
        *out_bold  = 1;
        return "  // syntax error";
    }

    return NULL;
}

void dice_completion_callback(const char * line, linenoiseCompletions * lc) {
    if (line[0] == '\0'
    || !strncmp(line, "dice", strlen(line))) {
        linenoiseAddCompletion(lc, "dice+");
    }
}

signed main(void) {
    linenoiseSetHintsCallback(dice_hints_callback);
    linenoiseSetCompletionCallback(dice_completion_callback);

    while (1) {
        char * input;
        char * output;

        input = linenoise("> ");
        output = qst_dice(input, false);

        if (output) {
            linenoiseHistoryAdd(input);
            puts(output);
        } else {
            puts("ERROR");
        }

        free(input);
        free(output);
    }

    return 0;
}
