%{
    #include "l.yy.h"

	int yyerror() { ; }
%}

%%
document
    : %empty
    ;
%%
