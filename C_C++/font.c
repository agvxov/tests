// @BAKE gcc $@ -o $*.out -ldictate -std=c2x -ggdb
#define _XOPEN_SOURCE 500
#include <dictate.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <fts.h>
#include <alloca.h>

enum {
    TTF_NORMAL     = 0b00,
    TTF_BOLD       = 0b01,
    TTF_ITALIC     = 0b10,
    TTF_BOLDITALIC = 0b11,
};

typedef struct {
    char * normal;
    char * bold;
    char * italic;
    char * bolditalic;
} ttf_quadruplet_t;

static inline
bool is_quadruplet_full(ttf_quadruplet_t q) {
    return q.normal
        && q.bold
        && q.italic
        && q.bolditalic
    ;
}

int ttf_style(const char * name) {
    int r = TTF_NORMAL;

    if (strstr(name, "bold"))    { r |= TTF_BOLD; }
    if (strstr(name, "italic"))  { r |= TTF_ITALIC; }
    if (strstr(name, "oblique")) { r |= TTF_ITALIC; }

    return r;
}

ttf_quadruplet_t load_font(const char * target_name) {
    const char * const fonts_path = "/usr/share/fonts/"; // XXX
    ttf_quadruplet_t r = (ttf_quadruplet_t){0};

    char * paths[] = {strdup(fonts_path), NULL};
    FTS *tree = fts_open(paths, FTS_PHYSICAL | FTS_NOCHDIR, NULL);
    if (!tree) { goto end; }

    FTSENT * entry;
    while ((entry = fts_read(tree)) != NULL) {
        if (entry->fts_info != FTS_F) { continue; }

        const char * path = entry->fts_path;
        const char * ext = strrchr(path, '.');
        if (!ext || strcmp(ext, ".ttf") != 0) { continue; }

        const char * base = entry->fts_name;

        char * lower_name = alloca(strlen(base));
        for (int i = 0; base[i] != '\0'; i++) {
            lower_name[i] = tolower(base[i]);
        }

        nftw

        if (!strstr(lower_name, target_name)) {
            continue;
        }

        int style = ttf_style(lower_name);
        switch (style) {
            case TTF_NORMAL:     r.normal     = strdup(base); break;
            case TTF_BOLD:       r.bold       = strdup(base); break;
            case TTF_ITALIC:     r.italic     = strdup(base); break;
            case TTF_BOLDITALIC: r.bolditalic = strdup(base); break;
        }

        if (is_quadruplet_full(r)) { break; }
    }

    fts_close(tree);

  end:
    return r;
}

int main() {
    ttf_quadruplet_t fonts;
    fonts = load_font("dejavusansmono");

    dictate(is_quadruplet_full(fonts), "\n");
    dictatef(
        "{ .n = '%s', .b = '%s', .i = '%s', .bl = '%s' }\n",
        fonts.normal,
        fonts.bold,
        fonts.italic,
        fonts.bolditalic
    );

    return 0;
}
