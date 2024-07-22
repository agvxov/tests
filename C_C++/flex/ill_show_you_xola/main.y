/*
  @BAKE
    bison --header=main.tab.h $@ -Wcounterexamples
    flex l.l
    gcc main.tab.c lex.yy.c -ggdb
    ./a.out
  @STOP
*/
%{
    #include <stdio.h>

    void yyerror() { ; }
%}
%token HEAD CIRCLE SQUARE TAIL
%%

document: %empty
    | document number
    ;

number: one
    | two
    | three
    ;

one: HEAD CIRCLE TAIL           { fputs("1", stdout); }
    ;

two: HEAD SQUARE TAIL           { fputs("2", stdout); }
    ;

three: HEAD SQUARE TAIL SQUARE   { fputs("3", stdout); }
%%

signed main() {
    yyparse();
    puts("");
    return 0;
}
