/* @BAKE
    bison --debug -Wcounterexamples --header=precedence.tab.h -o precedence.tab.c $@;
    gcc precedence.tab.c -o precedence;
    ./precedence;
   @STOP
*/
%{
#include <stdlib.h>
#include <stdio.h>
#include "precedence.tab.h"
int yylex() {
    static int i = 0;
    const int my_landscape[] = {'i', '+', 'i', '*', 'i', 0};
    return my_landscape[i++];
}
void yyerror() { exit(1); }
%}
%token A B C
%left '+'
%left '*'
%%
expr: 'i'
    | expr '+' expr { puts("+"); }
    | expr '*' expr { puts("*"); }
    ;
%%
signed main() {
    yydebug = 1;
    yyparse();
    return 0;
}
