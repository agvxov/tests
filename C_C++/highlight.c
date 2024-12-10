// @BAKE gcc -o $*.out $@ -ggdb
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#if 1
#define N_SPECIAL_BATCHES 3
struct {
    int color;
    const char * chars;
} specials[N_SPECIAL_BATCHES] = {
    {36, "./"},          // path
    {34, "0123456789"},  // numbers
    {31, ":(|&)[]{}-"},  // everything else
};

#define N_KEYWORD_BATCHES 6
struct {
    int color;
    const char * const * const keywords;
} keywords[N_KEYWORD_BATCHES] = {
    // Control
    {33, (const char * const[]) {"done", "do", "for", "in", "while", "select", "break", "continue", "exit", NULL}},
    // Input
    {35, (const char * const[]) {"read", "readarray", "compgen", "complete", "compopt", "bind", NULL}},
    // Bool
    {35, (const char * const[]) {"false", "true", NULL}},
    // Job Management
    {33, (const char * const[]) {"fg", "bg", "disown", "jobs", "kill", NULL}},
    // Directory manipulation
    {31, (const char * const[]) {"cd", "pwd", "popd", "pushd", "dirs", NULL}},
    // Misc.
    {33, (const char * const[]) {"alias", "builtin", "caller", "command", "declare", "echo", "enable", "export", "eval", "exec", "fc", "getopts", "hash", "help", "history", "let", "local", "logout", "mapfile", "printf", "readonly", "return", "set", "shift", "shopt", "source", "suspend", "test", "times", "trap", "type", "typeset", "ulimit", "umask", "unalias", "unset", "wait", NULL}},
};

#define N_REGIONS 4
struct {
    int color;
    const char * start;
    const char * end;
} regions[N_REGIONS] = {
    {32, "\"", "\""},
    {32, "'", "'"},
    {34, "${", "}"},
    {34, "#", "\n"},
};
#else
#define N_SPECIAL_BATCHES 1
struct {
    int color;
    const char * chars;
} specials[N_SPECIAL_BATCHES] = {
    {36, ".,:;<=>+-*%!&~^?|()[]{}"},
};

#define N_KEYWORD_BATCHES 1
struct {
    int color;
    const char * const * const keywords;
} keywords[N_KEYWORD_BATCHES] = {
    // Control
    {33, (const char * const[]) {
        "register",     "volatile",     "auto",         "const",        "static",       "extern",       "if",           "else",
		"do",           "while",        "for",          "continue",     "switch",       "case",         "default",      "break",
		"enum",         "union",        "struct",       "typedef",      "goto",         "void",         "return",       "sizeof",
		"char",         "short",        "int",          "long",         "signed",       "unsigned",     "float",        "double",
        NULL
    }},
};

#define N_REGIONS 4
struct {
    int color;
    const char * start;
    const char * end;
} regions[N_REGIONS] = {
    {32, "\"", "\""},
    {32, "'", "'"},
    {34, "//", "\n"},
    {34, "/*", "*/"},
};
#endif

void highlight(const char * s, int * pos, int * len, int * color) {
    const char * s_base = s;
    for (; *s != '\0'; s++) {
        for (int i = 0; i < N_SPECIAL_BATCHES; i++) {
            for (const char * ss = specials[i].chars; *ss != '\0'; ss++) {
                if (*ss == *s) {
                    *pos = s - s_base;
                    *len = 1;
                    *color = specials[i].color;
                    return;
                }
            }
        }

        for (int i = 0; i < N_KEYWORD_BATCHES; i++) {
            for (const char * const * ss = keywords[i].keywords; *ss != NULL; ss++) {
                if (!strncmp(s, *ss, strlen(*ss))) {
                    *pos = s - s_base;
                    *len = strlen(*ss);
                    *color = keywords[i].color;
                    return;
                }
            }
        }

        for (int i = 0; i < N_REGIONS; i++) {
            if (!strncmp(s, regions[i].start, strlen(regions[i].start))) {
                *pos = s - s_base;
                while (1) {
                    ++s;
                    if (*s == '\0') {
                        goto end;
                    }
                    if (*s == '\\') {
                        if (*(s+1) == '\\') {
                            ++s;
                            continue;
                        }
                        if (!strncmp(s+1, regions[i].end, strlen(regions[i].end))) {
                            s += strlen(regions[i].end);
                            continue;
                        }
                    }
                    if (!strncmp(s, regions[i].end, strlen(regions[i].end))) {
                        goto end;
                    }

                    continue;
                  end:
                    *len = ((s - s_base) - *pos) + 1;
                    *color = regions[i].color;
                    return;
                }
            }
        }
    }

    *pos = s - s_base;
    *len = 0;
    *color = 0;
    return;
}

signed main(int argc, char * argv[]) {
    //const char * input = "for i in 1 2 3 4 5; do echo \"test\\\"${i}\"; done; A=${i}\n";
	FILE* f = fopen(argv[1], "r"); // XXX segv warning

	fseek(f, 0, SEEK_END);
	int flen = ftell(f);
	rewind(f);
	char fstr[flen+1];
	fstr[flen] = '\00';
	fread(fstr, flen, sizeof(char), f);

	fclose(f);

    const char * input = fstr;
    int pos, len, color;

    for (const char * s = input; *s != '\0';) {
        highlight(s, &pos, &len, &color);
        printf("%.*s\033[%dm%.*s\033[0m", pos, s, color, len, s + pos);
        s += pos + len;
    }
}
