%option noyywrap
%%
. { /*MYMARK*/; }
%%

void main(int argc, char * argv[]) {
    yyin = argc[0];
    yylex();
}
