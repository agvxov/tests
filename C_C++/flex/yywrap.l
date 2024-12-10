/* @BAKE
    flex -o $*.yy.c $@
    gcc $*.yy.c
    ./a.out yywrap.l
   @STOP
 */
%%

%%

int yywrap() {
    puts("--");

    fclose(yyin);

    yyin = fopen(__FILE__, "r");

    return 0;
}

signed main(int argc, char * argv[]) {
    yyin = fopen(__FILE__, "r");
    yylex();

    return 0;
}
