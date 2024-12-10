/* @BAKE
    re2c -W -o $*.re.c $@
    gcc -o $* $*.re.c -ggdb
    ./$* pure_hw.bf
   @STOP
 */
#include <stdio.h>

char data[30000];
char * data_ptr = data;

// #define YYDEBUG(n, c) fprintf(stderr, "rule %n (%c)\n", l, c)

/* Review of this bullshit software called re2c 3.1:
 *  + the comment thing is kinda smart
 *    - it generates very small scanners so having them inline is not insanity
 *    - you can nest them in your source, without breaking your highlighting or making the lls cry
 *  + it can generate state transition graphs, thats kinda cool
 *  + neither the "free-form" or the "function-like" API seems to work;
 *     theres no error or acknoledgement either
 *  + the first example in the documentation is fucking broken
 *    - it uses undocumented cli flags (like some others)
 *    - they feed a string, but only one character is ever evaluated
 *  + '\00' gives a syntax error for no damn reason
 *  + switches it generates hurt my eye. why the fuck do they need a label and a goto for each case?,
 *     sure there is string/regex matching which cannot fit inside a case,
 *     however what if only those were to jmp?
 *  + the default rule ('*') is not properly documented
 *  + for whatever reason fallthough is the default behaviour so you have to spam either
 *     continue or goto
 *  + the default default rule is a fallthrough too;
 *     not a jam, but whatever rule the transpiler decided to insert to the top
 *     (spoiler alert: they are not even in the order of declaration)
 *  + what the literal fuck is this syntax?
 *     `re2c:api:style`
 *     1) you dont need the prefix re2c, its utter bloat
 *     2) namespacing for 20 or so options???
 *     3) my bad, *should be 20 so optoins, instead we have shit like this:
 *          re2c:bit-vectors, re2c:flags:bit-vectors, re2c:flags:b
 *        to do the same fucking thing
 *        and just to stress this, they have namespaces, but you can just no use them.
 *        when? option dependent.
 *  + do we have comments inside re2c blocks? dunno. not documented.
 *  + the cli help is too verbose; useless line breaks makes it hard to grep
 *  + while we are at it, why do we need so many fucking options?
 *      $ re2c --help | grep -e '^\W*-' | sort | uniq | wc -l
 *      77
 *      $ flex --help | grep -e '^\W*-' | sort | uniq | wc -l
 *      46
 *      # and this shit is suppose to be smaller
 *  + -d is useless; YYDEBUG is simply not fit to tracing, since it does not tell you
 *    which lexer it is or the line number
 *  + i get duplicate output. now, it very well might be my fault,
 *     however i have no proper means of debugging and im not
 *     wasting more time on this software
 */

int yylex(const char * const s) {
    const char * YYCURSOR = s;

  INITIAL:
    while (*YYCURSOR)
        /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;

        '>'     { ++data_ptr; continue; }
        '<'     { --data_ptr; continue; }
        '+'     { ++(*data_ptr); continue; }
        '-'     { --(*data_ptr); continue; }
        '.'     { putchar(*data_ptr); continue; }
        ','     { *data_ptr = getchar(); continue; }
        '['     {
                  if (!*data_ptr) {
                       goto IN_SKIP_FORWARD;
                  }
                  continue;
                }
        ']'     {
                  if (!*data_ptr) {
                       goto IN_SKIP_BACKWARD;
                  }
                  continue;
                }
        *       { continue; }
        '\x00'  { return 0; }
        */

  IN_SKIP_FORWARD:
    while (*YYCURSOR)
        /*!re2c

        ']'     {
                  goto INITIAL;
                }
        *       { continue; }
        '\x00'  { return 0; }
         */
    /* I cant seem to make this thing go backwards,
     *  so everything is broken
     */
  IN_SKIP_BACKWARD:
  #define YYSKIP --YYCURSOR
    while (*YYCURSOR)
        /*!re2c
        //re2c:api:style     = free-form;
        //re2c:define:YYSKIP = "--YYCURSOR;";

        '['     {
                  ++YYCURSOR;
                  goto INITIAL;
                }
        *       { continue; }
        '\x00'  { return 0; }
         */

    return 0;
}

signed main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("%s <file>", argv[0]);
        return 1;
    }

	FILE* f = fopen(argv[1], "r");
	if(!f){ return 2; }

	fseek(f, 0, SEEK_END);
	int flen = ftell(f);
	rewind(f);
	char fstr[flen+1];
	fstr[flen] = '\00';
	fread(fstr, flen, sizeof(char), f);

	fclose(f);

    yylex(fstr);

    return 0;
}
