/* @BAKE
    bison -Wcounterexamples --header=error.tab.h -o error.tab.c $@;
    gcc error.tab.c -o error;
    ./error;
   @STOP
*/
%{
#include <stdlib.h>
#include <stdio.h>
#include "error.tab.h"
int yylex() {
    static int i = 0;
    const int alpha[] = {B, 0};
    return alpha[i++];
}
void yyerror() { ; }
%}
%token A B
%%
i: A
    | error B    { yyerrok; puts("We recovered!"); }
    ;
%%
signed main() {
    yyparse();
    return 0;
}
