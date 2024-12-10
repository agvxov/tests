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
    const int my_story[] = {PLOT, PLOT, ACTION, BOSSFIGHT, 0};
    //const int my_story[] = {PLOT, PLOT, ACTION, ACTION, 0};
    //const int my_story[] = {0};
    return my_story[i++];
}
void yyerror() {
    puts("Not a story.");
    exit(1);
}
%}
%token BOOORING PLOT ACTION BOSSFIGHT
%%

story: start middle ending
    ;

start:  %empty
    | BOOORING PLOT
    ;

submid: %empty
    | submid ACTION
    | submid PLOT
    ;

middle: submid ACTION
    | submid PLOT
    ;

ending: %empty
    | BOSSFIGHT
    ;

%%
signed main() {
    yyparse();
    puts("It is a story.");
    return 0;
}
