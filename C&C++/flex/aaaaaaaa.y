/* @BAKE
	bison --header=a.tab.h -o a.tab.c $@
	g++ a.tab.c -o a
	./a
   @STOP
*/
%code requires {
	#include <iostream>
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
