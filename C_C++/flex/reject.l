/* @BAKE
    flex $@
    gcc lex.yy.c -lfl
    ./a.out
   @STOP
*/
%option reject
%%
a        |
ab       |
abc      |
abcd     REJECT; ECHO; 
.|\n     /* eat up any unmatched character */
