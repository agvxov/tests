%{
	#include <stdio.h>
%}

%%
hello   printf("World!\n");
%{
	int i;
%}
%%

int main() {
    yylex();
    return 0;
}
