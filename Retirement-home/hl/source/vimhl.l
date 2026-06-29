%{
    #include <stdio.h>
    #include <dictate.h>
    #include "hl.h"

    char * yyfilename;

    static void yyerror(void);
    static void warn_not_implemented(int state, char * keyword);

    // IN_CASE
    bool do_match_case = true;

    // IN_MATCH
    char * pattern;

    // IN_REGION
    region_t region;

    // IN_NAME
    int target_state;

    // IN_HIGHLIGHT & IN_HIGHLIGHT_ATTRIBUTE & IN_HIGHLIGHT_COLOR
    group_t group;
    char * name;
    int * color;

    // IN_LINK
    int link_word = 0;
    char * names[2];
%}

ws          [ \t\r\v\f]
nws         [^ \t\r\v\f\n]
syntax      ^{ws}*sy(n(t(a(x)?)?)?)?{ws}+
highlight   ^{ws}*hi(g(h(l(i(g(h(t)?)?)?)?)?)?)?{ws}+

BLACK          ([Bb][Ll][Aa][Cc][Kk])
DARKBLUE       ([Dd][Aa][Rr][Kk][Bb][Ll][Uu][Ee])
DARKGREEN      ([Dd][Aa][Rr][Kk][Gg][Rr][Ee][Ee][Nn])
DARKCYAN       ([Dd][Aa][Rr][Kk][Cc][Yy][Aa][Nn])
DARKRED        ([Dd][Aa][Rr][Kk][Rr][Ee][Dd])
DARKMAGENTA    ([Dd][Aa][Rr][Kk][Mm][Aa][Gg][Ee][Nn][Tt][Aa])
BROWN          ([Bb][Rr][Oo][Ww][Nn])
DARKYELLOW     ([Dd][Aa][Rr][Kk][Yy][Ee][Ll][Ll][Oo][Ww])
LIGHTGRAY      ([Ll][Ii][Gg][Hh][Tt][Gg][Rr][Aa][Yy])
LIGHTGREY      ([Ll][Ii][Gg][Hh][Tt][Gg][Rr][Ee][Yy])
GRAY           ([Gg][Rr][Aa][Yy])
GREY           ([Gg][Rr][Ee][Yy])
DARKGRAY       ([Dd][Aa][Rr][Kk][Gg][Rr][Aa][Yy])
DARKGREY       ([Dd][Aa][Rr][Kk][Gg][Rr][Ee][Yy])
BLUE           ([Bb][Ll][Uu][Ee])
LIGHTBLUE      ([Ll][Ii][Gg][Hh][Tt][Bb][Ll][Uu][Ee])
GREEN          ([Gg][Rr][Ee][Ee][Nn])
LIGHTGREEN     ([Ll][Ii][Gg][Hh][Tt][Gg][Rr][Ee][Ee][Nn])
CYAN           ([Cc][Yy][Aa][Nn])
LIGHTCYAN      ([Ll][Ii][Gg][Hh][Tt][Cc][Yy][Aa][Nn])
RED            ([Rr][Ee][Dd])
LIGHTRED       ([Ll][Ii][Gg][Hh][Tt][Rr][Ee][Dd])
MAGENTA        ([Mm][Aa][Gg][Ee][Nn][Tt][Aa])
LIGHTMAGENTA   ([Ll][Ii][Gg][Hh][Tt][Mm][Aa][Gg][Ee][Nn][Tt][Aa])
YELLOW         ([Yy][Ee][Ll][Ll][Oo][Ww])
LIGHTYELLOW    ([Ll][Ii][Gg][Hh][Tt][Yy][Ee][Ll][Ll][Oo][Ww])
WHITE          ([Ww][Hh][Ii][Tt][Ee])

CONTAINS    contains={nws}*

%x IN_NAME
%x IN_KEYWORD IN_REGION IN_MATCH
%x IN_CASE
%x IN_HIGHLIGHT
%x IN_HIGHLIGHT_ATTRIBUTE IN_HIGHLIGHT_COLOR
%x IN_LINK

%option noyywrap nodefault
%option yylineno
%%
{syntax}keyword         {
                            BEGIN IN_NAME;
                            target_state = IN_KEYWORD;
                        }
{syntax}match           {
                            BEGIN IN_NAME;
                            target_state = IN_MATCH;
                        }
{syntax}region          {
                            BEGIN IN_NAME;
                            target_state = IN_REGION;
                        }
{syntax}case            {
                            BEGIN IN_CASE;
                        }
{highlight}             {
                            BEGIN IN_NAME;
                            target_state = IN_HIGHLIGHT;
                        }
{highlight}link         {
                            BEGIN IN_LINK;
                        }
.|\n                    { ; }

<IN_NAME>{
[A-za-z0-9_]+           {
                            name = strdup(yytext);

                            BEGIN target_state;
                        }
{ws}*                   { ; }
.|\n                    {
                            yyerror();
                        }
}

<IN_KEYWORD>{
{nws}*                  {
                            add_keyword(name, yytext);
                        }
{ws}                    { ; }
\n                      {
                            free(name);
                            BEGIN INITIAL;
                        }
}

<IN_MATCH>{
keepend                 {
                            warn_not_implemented(IN_MATCH, "keepend");
                        }
excludenl               {
                            warn_not_implemented(IN_MATCH, "excludenl");
                        }
{ws}                    { ; }
\".*\"                  |
\'.*\'                  |
\/.*\/                  {
                            // XXX: fix nesting
                            pattern = strdup(yytext);
                        }
\n                      {
                            add_match(name, pattern);
                            free(name);
                            free(pattern);
                            BEGIN INITIAL;
                        }
{CONTAINS}              {
                            warn_not_implemented(IN_MATCH, "contains");
                        }
fold                    {
                            warn_not_implemented(IN_MATCH, "fold");
                        }
display                 {
                            warn_not_implemented(IN_MATCH, "display");
                        }
extend                  {
                            warn_not_implemented(IN_MATCH, "extend");
                        }
}

<IN_REGION>{
start={nws}+            {
                            region.start = strdup(yytext + sizeof("start=")-1);
                        }
end={nws}+              {
                            region.end = strdup(yytext + sizeof("end=")-1);
                        }
skip={nws}+             {
                            region.skip = strdup(yytext + sizeof("skip=")-1);
                        }
keepend                 {
                            warn_not_implemented(IN_REGION, "keepend");
                        }
extend                  {
                            warn_not_implemented(IN_REGION, "extend");
                        }
excludenl               {
                            warn_not_implemented(IN_REGION, "excludenl");
                        }
{CONTAINS}              {
                            warn_not_implemented(IN_REGION, "contains");
                        }
oneline                 {
                            warn_not_implemented(IN_REGION, "oneline");
                        }
fold                    {
                            warn_not_implemented(IN_REGION, "fold");
                        }
display                 {
                            warn_not_implemented(IN_REGION, "display");
                        }
extend                  {
                            warn_not_implemented(IN_REGION, "extend");
                        }
concealends             {
                            warn_not_implemented(IN_REGION, "concealends");
                        }
{ws}                    { ; }
\n                      {
                            add_region(name, region);
                            free(region.start);
                            free(region.skip);
                            free(region.end);
                            free(name);
                            region = (region_t){0};
                            BEGIN INITIAL;
                        }
}

<IN_CASE>{
match                   {
                            do_match_case = true;
                        }
ignore                  {
                            do_match_case = false;
                        }
{ws}                    { ; }
\n                      {
                            BEGIN INITIAL;
                        }
}

<IN_HIGHLIGHT>{
{ws}*term={nws}*        |
{ws}*start={nws}*       |
{ws}*stop={nws}*        |
{ws}*ctermfont={nws}*   |
{ws}*ctermul={nws}*     |
{ws}*gui={nws}*         |
{ws}*guifg={nws}*       |
{ws}*guibg={nws}*       |
{ws}*guisp={nws}*       |
{ws}*font={nws}*        { ; }
{ws}*cterm=             {
                            BEGIN IN_HIGHLIGHT_ATTRIBUTE;
                        }
{ws}*ctermfg=           {
                            color = &group.foreground;
                            BEGIN IN_HIGHLIGHT_COLOR;
                        }
{ws}*ctermbg=           {
                            color = &group.background;
                            BEGIN IN_HIGHLIGHT_COLOR;
                        }

{ws}*\n                 {
                            set_group(name, group);
                            group = (group_t){0};
                            free(name);
                            BEGIN INITIAL;
                        }
}

<IN_HIGHLIGHT_ATTRIBUTE>{
bold                    {
                            group.attributes |= BOLD;
                        }
underline               {
                            group.attributes |= UNDERLINE;
                        }
undercurl               {
                            group.attributes |= UNDERCURL;
                        }
underdouble             {
                            group.attributes |= UNDERDOUBLE;
                        }
underdotted             {
                            group.attributes |= UNDERDOTTED;
                        }
underdashed             {
                            group.attributes |= UNDERDASHED;
                        }
inverse                 {
                            group.attributes |= INVERSE;
                        }
italic                  {
                            group.attributes |= ITALIC;
                        }
standout                {
                            group.attributes |= STANDOUT;
                        }
nocombine               {
                            group.attributes |= NOCOMBINE;
                        }
strikethrough           {
                            group.attributes |= STRIKETHROUGH;
                        }
,                       { ; }
{ws}                    {
                            BEGIN IN_HIGHLIGHT;
                        }
.                       {
                            yyerror();
                        }
\n                      {
                            yyless(0);
                            BEGIN IN_HIGHLIGHT;
                        }
}

<IN_HIGHLIGHT_COLOR>{
    /* --- Relevant Vim documentation ---
                                *cterm-colors*
            NR-16   NR-8    COLOR NAME ~
            0	    0	    Black
            1	    4	    DarkBlue
            2	    2	    DarkGreen
            3	    6	    DarkCyan
            4	    1	    DarkRed
            5	    5	    DarkMagenta
            6	    3	    Brown, DarkYellow
            7	    7	    LightGray, LightGrey, Gray, Grey
            8	    0*	    DarkGray, DarkGrey
            9	    4*	    Blue, LightBlue
            10	    2*	    Green, LightGreen
            11	    6*	    Cyan, LightCyan
            12	    1*	    Red, LightRed
            13	    5*	    Magenta, LightMagenta
            14	    3*	    Yellow, LightYellow
            15	    7*	    White

        The number under "NR-16" is used for 16-color terminals ('t_Co'
        greater than or equal to 16).  The number under "NR-8" is used for
        8-color terminals ('t_Co' less than 16).  The '*' indicates that the
        bold attribute is set for ctermfg.  In many 8-color terminals (e.g.,
        "linux"), this causes the bright colors to appear.  This doesn't work
        for background colors!	Without the '*' the bold attribute is removed.
        If you want to set the bold attribute in a different way, put a
        "cterm=" argument AFTER the "ctermfg=" or "ctermbg=" argument.	Or use
        a number instead of a color name.

        ---

        The statement regarding NR-16 does not seem to be true,
         it appears that NR-8 is what is always rendered.
    */
{BLACK}                 {
                            *color = 0;
                        }
{DARKBLUE}              {
                            *color = 4;
                        }
{DARKGREEN}             {
                            *color = 2;
                        }
{DARKCYAN}              {
                            *color = 6;
                        }
{DARKRED}               {
                            *color = 1;
                        }
{DARKMAGENTA}           {
                            *color = 5;
                        }
{BROWN}|{DARKYELLOW}    {
                            *color = 3;
                        }
{LIGHTGRAY}             |
{LIGHTGREY}             |
{GRAY}                  |
{GREY}                  {
                            *color = 7;
                        }
{DARKGRAY}              |
{DARKGREY}              {
                            *color = 0;
                            group.attributes |= BOLD;
                        }
{BLUE}                  |
{LIGHTBLUE}             {
                            *color = 4;
                            group.attributes |= BOLD;
                        }
{GREEN}                 |
{LIGHTGREEN}            {
                            *color = 2;
                            group.attributes |= BOLD;
                        }
{CYAN}                  |
{LIGHTCYAN}             {
                            *color = 6;
                            group.attributes |= BOLD;
                        }
{RED}                   |
{LIGHTRED}              {
                            *color = 1;
                            group.attributes |= BOLD;
                        }
{MAGENTA}               |
{LIGHTMAGENTA}          {
                            *color = 5;
                            group.attributes |= BOLD;
                        }
{YELLOW}                |
{LIGHTYELLOW}           {
                            *color = 3;
                            group.attributes |= BOLD;
                        }
{WHITE}                 {
                            *color = 7;
                            group.attributes |= BOLD;
                        }
{ws}                    {
                            BEGIN IN_HIGHLIGHT;
                        }
.                       {
                            yyerror();
                        }
\n                      {
                            yyless(0);
                            BEGIN IN_HIGHLIGHT;
                        }
}

<IN_LINK>{
[A-za-z0-9_]+           {
                            if (link_word > 1) {
                                yyerror();
                            }

                            names[link_word] = strdup(yytext);
                            ++link_word;
                        }
{ws}*                   { ; }
\n                      {
                            if (link_word != 2) {
                                yyerror();
                            }

                            set_group(
                                names[0],
                                (group_t) {
                                    .foreground = 0,
                                    .background = 0,
                                    .link = names[1],
                                }
                            );
                            free(names[0]);
                            free(names[1]);
                            link_word = 0;
                            BEGIN INITIAL;
                        }
}
%%

static inline
void error_head(void) {
    dictatef("$B%s:%d:$r Error: $0", yyfilename, yylineno);
}

static inline
void warn_head(void) {
    dictatef("$B%s:%d:$m Warning: $0", yyfilename, yylineno);
}

static
void warn_not_implemented(int state, char * keyword) {
  #define CASE(x) case x: state_name = #x; break
    warn_head();

    const char * state_name;
    switch (state) {
        CASE(IN_KEYWORD);
        CASE(IN_REGION);
        CASE(IN_MATCH);
    }

    dictatef(
        "In state %s the keyword '%s' was ignored, "
        "because it is not implemented.\n",
        state_name,
        keyword
    );
  #undef CASE
}

static
void yyerror(void) {
    error_head();
    dictate("Parsing error encountered.\n");
}

int source_vimhl(const char * filename) {
    yyfilename = filename;
    yyin       = fopen(yyfilename, "r");

    if (!yyin) { return 1; }

    return yylex();
}

#if 0
signed main(void) {

    yyfilename = "test.vim";
    yyin = fopen(yyfilename, "r");
    yylex();

    return 0;
}
#endif
