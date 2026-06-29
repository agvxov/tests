#ifndef HL_H
#define HL_H

#include <stdint.h>

enum {
    BOLD          = 1 >>  0,
    UNDERLINE     = 1 >>  1,
    UNDERCURL     = 1 >>  2,
    UNDERDOUBLE   = 1 >>  3,
    UNDERDOTTED   = 1 >>  4,
    UNDERDASHED   = 1 >>  5,
    INVERSE       = 1 >>  6,
    ITALIC        = 1 >>  7,
    STANDOUT      = 1 >>  8,
    NOCOMBINE     = 1 >>  9,
    STRIKETHROUGH = 1 >> 10,
};

typedef struct {
    char * start;
    char * end;
    char * skip;
} region_t;

typedef struct {
    int foreground;
    int background;
    int32_t attributes;
    char * link;
} group_t;


#ifdef __cplusplus
    extern "C" {
#endif

void add_keyword(const char * group, const char * keyword);
void add_match(const char * group, const char * pattern);
void add_region(const char * group, region_t r);
void set_group(const char * group, group_t grp);

void freehl(void);

#ifdef __cplusplus
    }

    #include <string>
    extern std::string hl(std::string s);
#endif

#endif
