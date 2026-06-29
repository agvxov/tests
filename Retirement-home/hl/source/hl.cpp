#include <stdlib.h>
#include <string.h>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <stdexcept>
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#include <dictate.hpp>

#include "hl.h"

static inline
void dictate_switch(DICTATEPP_PRINTER_COMMON_ARGS, const region_t i) {
    fprintf(f, "{ .start='%s', .end='%s', .skip='%s' }", i.start, i.end, i.skip);
}

extern std::string vim2pcre(const char * pattern);

using namespace std;

typedef struct {
    string group;
    pcre2_code * regex;
} hl_t;

map<string, group_t> groups;
vector<hl_t> regexes;

group_t resolve_group_link(string name) {
    group_t r = { 0 };

    try {
        r = groups.at(name);
    } catch (std::out_of_range e) {
        // XXX bad error handling
        dictatef("$B%s:%d$m Warning: $0 No such group '%s'.\n", "input", 0, name.c_str());
        return r;
    }

    if (r.link) {
        r = resolve_group_link(r.link);
    }

    return r;
}


string get_substitute(group_t group) {
    string r;

    r += "\033[38;5;";
    r += to_string(group.foreground);
    r += "m";

    r += "\033[48;5;";
    r += to_string(group.background);
    r += "m";

    // XXX: figure out a clean conversion
    if (group.attributes & BOLD) {
        r += "\033[1m";
    }

    r += "$0\033[0m";

    return r;
}

string hl(string s) {
    // XXX: init hack
    groups["Comment"] = (group_t) {
        .foreground = 6,
        .background = 0,
        .attributes = BOLD,
        .link       = NULL,
    };
    groups["Constant"] = (group_t) {
        .foreground = 5,
        .background = 0,
        .attributes = BOLD,
        .link       = NULL,
    };
    groups["Special"] = (group_t) {
        .foreground = 1,
        .background = 0,
        .attributes = BOLD,
        .link       = NULL,
    };
    groups["Identifier"] = (group_t) {
        .foreground = 6,
        .background = 0,
        .attributes = BOLD,
        .link       = NULL,
    };
    groups["Statement"] = (group_t) {
        .foreground = 3,
        .background = 0,
        .attributes = BOLD,
        .link       = NULL,
    };
    groups["PreProc"] = (group_t) {
        .foreground = 4,
        .background = 0,
        .attributes = BOLD,
        .link       = NULL,
    };
    groups["Type"] = (group_t) {
        .foreground = 2,
        .background = 0,
        .attributes = BOLD,
        .link       = NULL,
    };
    groups["Underlined"] = (group_t) {
        .foreground = 4,
        .background = 0,
        .attributes = BOLD,
        .link       = NULL,
    };
    groups["Ignore"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = NULL,
    };
    groups["Added"] = (group_t) {
        .foreground = 2,
        .background = 0,
        .attributes = BOLD,
        .link       = NULL,
    };
    groups["Changed"] = (group_t) {
        .foreground = 4,
        .background = 0,
        .attributes = BOLD,
        .link       = NULL,
    };
    groups["Removed"] = (group_t) {
        .foreground = 1,
        .background = 0,
        .attributes = BOLD,
        .link       = NULL,
    };
    //
    groups["String"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Constant"),
    };

    groups["Character"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Constant"),
    };

    groups["Number"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Constant"),
    };

    groups["Boolean"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Constant"),
    };

    groups["Float"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Number"),
    };

    groups["Function"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Identifier"),
    };

    groups["Conditional"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Statement"),
    };

    groups["Repeat"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Statement"),
    };

    groups["Label"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Statement"),
    };

    groups["Operator"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Statement"),
    };

    groups["Keyword"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Statement"),
    };

    groups["Exception"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Statement"),
    };

    groups["Include"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("PreProc"),
    };

    groups["Define"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("PreProc"),
    };

    groups["Macro"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("PreProc"),
    };

    groups["PreCondit"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("PreProc"),
    };

    groups["StorageClass"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Type"),
    };

    groups["Structure"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Type"),
    };

    groups["Typedef"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Type"),
    };

    groups["Tag"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Special"),
    };

    groups["SpecialChar"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Special"),
    };

    groups["Delimiter"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Special"),
    };

    groups["SpecialComment"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Special"),
    };

    groups["Debug"] = (group_t) {
        .foreground = 0,
        .background = 0,
        .attributes = 0,
        .link       = strdup("Special"),
    };
    //

    int replaced_length;
    PCRE2_UCHAR * result = NULL;

    PCRE2_SIZE outlength = s.size() * 4; // XXX: shitty estimate

    result = (PCRE2_UCHAR*)malloc(outlength);

    for (auto i : groups) {
        debug_dictatef(
            "{ .n = %s, .l = %s, .f = %d, a = %d }\n",
            i.first.c_str(),
            i.second.link,
            i.second.foreground,
            i.second.attributes
        );
    }

    for (auto hl : regexes) {
        auto re = hl.regex;
        group_t group = resolve_group_link(hl.group);

        string substitute = get_substitute(group);

        pcre2_substitute(
            re,
            (PCRE2_SPTR)s.c_str(),
            s.size(),
            0,
            PCRE2_SUBSTITUTE_GLOBAL,
            NULL,
            NULL,
            (PCRE2_SPTR)substitute.c_str(),
            substitute.size(),
            result,
            &outlength
        );
        s = (char*)result;
    }

    free(result);

    return s;
}

void freehl(void) {
    for (auto i : regexes) {
        pcre2_code_free(i.regex);
    }

    for (auto i : groups) {
        free(i.second.link);
    }
}

// ---
#define ADD_REGEX(g, x) do {          \
    debug_dictate(                    \
        "Recieved concrate regex: '", \
        x,                            \
        "'.\n"                        \
    );                                \
    PCRE2_SIZE erroffset;             \
    int errorcode;                    \
    pcre2_code * re = pcre2_compile(  \
        (PCRE2_SPTR)x.c_str(),        \
        PCRE2_ZERO_TERMINATED,        \
        PCRE2_MULTILINE,              \
        &errorcode,                   \
        &erroffset,                   \
        NULL                          \
    );                                \
                                      \
    if (!re) { abort(); }             \
                                      \
    regexes.push_back((hl_t) {        \
        .group = g,                   \
        .regex = re,                  \
    });                               \
} while (0)

// --- Keywords ---
static
string shorten_keyword_recurse(string r) {
    if (r.size() != 1) {
        r = shorten_keyword_recurse(r.substr(1));
    }

    return string() + "(" + r + ")?";
}

static
string shorten_keyword(string r) {
    if (r[r.size()-1] != ']') { return r; }

    int i = 0;
    for (int i = 0; r[i] != '['; i++) { ; }

    return r.substr(0, i) + shorten_keyword_recurse(r.substr(i));
}

extern "C"
void add_keyword(const char * group, const char * keyword) {
    string p;
    p = keyword;
    p = shorten_keyword(p);
    p = "\\b" + p + "\\b";

    debug_dictatef("Added keyword '%s'.\n", keyword);

    ADD_REGEX(group, p);
}

// --- Matches ---
extern "C"
void add_match(const char * group, const char * pattern) {
    string p;
    p = vim2pcre(pattern);

    debug_dictatef("Added match '%s'.\n", pattern);

    ADD_REGEX(group, p);
}

// --- Regions ---
extern "C"
void add_region(const char * group, region_t r) {
    string s, k, e, p;
    s = vim2pcre(r.start);
    e = vim2pcre(r.end);
    k = r.skip
            ? string() + "[^" + vim2pcre(r.skip) + "]*?"
            : ".*?"
    ;
    p = s + k + e;

    debug_dictate("Added region '", r, "'.\n");

    ADD_REGEX(group, p);
}

// --- Groups ---
extern "C"
void set_group(const char * group, group_t grp) {
    debug_dictate("Bumped group '", group, "'.\n");

    groups[group] = (group_t) {
        .foreground = grp.foreground,
        .background = grp.background,
        .attributes = grp.attributes,
        .link       = grp.link ? strdup(grp.link) : grp.link,
    };
}
