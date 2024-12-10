/* @BAKE
    bison -o string.tab.c $@
    g++ string.tab.c -o string
    ./string
   @STOP
*/
%code requires {
    #include <iostream>
    #include <string>
    void yyerror(...) { ; }
}
%union {
    std::string * strval;
}
%{
    int yylex() {
        yylval.strval = new std::string("There are only two hard problems in CS: cache invalidation, nameing things, and off-by-one errors.");
        return STRING;
    }
%}
%token STRING
%%
string: STRING { std::cout << *(yylval.strval) << std::endl; }
%%
signed main() { yyparse(); }
