/* @BAKE
    bison -Wcounterexamples --header=story.tab.h -o story.tab.c $@;
    gcc story.tab.c -o story;
    ./story;
   @STOP
*/
%{
#include <stdio.h>
#include <stdlib.h>
#include "story.tab.h"
int yylex() {
    static int i = 0;
    const char * const my_values[] = {"head", "body", "tail-1", "tail-2"};
    const int          my_tokens[] = { HEAD,   BODY,   TAIL,     TAIL,     0};
    yylval.strval = my_values[i];
    return my_tokens[i++];
}
void yyerror() { exit(1); }
%}
%union {
    const char * strval;
}
%token <strval> HEAD BODY TAIL
%%

kutya_part: HEAD BODY tail
    ;

tail: TAIL TAIL  { printf("%s %s %s %s\n", $<strval>-1, $<strval>0, $1, $2); }
    ;

%%
signed main() {
    yyparse();
    return 0;
}
