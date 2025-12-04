%{
/* @BAKE
    bison hw.y -o hw.yy.c
    gcc hw.yy.c -std=c23
   @STOP
 */
// Q: does bison not compile under c23 at all?
// A: it does compile, im in some kind of macro hell in tbsp,
//     where fileno() is documented to require __POSIX_C_SOURCE,
//     which bison does define, alone with __POSIX_SOURCE,
//     but for some forsaken reason its actually __USE_POSIX that is required
int yylex(...) { ; }
int yyerror(...) { ; }
%}

%%
document : %empty;
%%

signed main() { ; }
