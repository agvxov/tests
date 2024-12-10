/* @BAKE
    flex -o scan_string.yy.c $@
    gcc  -o scan_string.out  scan_string.yy.c
    ./scan_string.out
   @STOP
 */
%option noyywrap
%%
%%
signed main() {
    const char * input = "This is my input";
    YY_BUFFER_STATE const b = yy_scan_string(input);
    yylex();
    yy_delete_buffer(b);
}
