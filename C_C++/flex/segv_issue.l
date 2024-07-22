/* @BAKE
    flex -o $*.c $@
    cc -o eof $*.c -ggdb -lfl
   @STOP
*/
ALPHABETIC  [a-zA-Z]
WS          [^a-zA-Z!]

%option

%%

{ALPHABETIC}+   {
    ECHO;
    return 1;
}
{WS}+   {
    ECHO;
    return 2;
}

"!"         {
    char buf[80];
    for (int idx=0; (buf[idx] = input()); idx++) /* empty */ ;
    printf("buf=<%s>\n", buf);
    // YY_FLUSH_BUFFER; /* makes no difference */
    return 3;
    ECHO;
    char c;
    while (c = input()) {
        printf("'%c'\n", c);
    }
    return 3;
}

%%
int main(int argc, const char * const * const argv)
{
    /*
    switch (argc) {
      case 1: break;
      case 2:
        yy_scan_string(argv[1]);
        break;
      default:
        fprintf(stderr, "Usage: %s [string]\n", argv[0]);
        exit(1);
    }
    */

    const char * test = "one two !three four";
    yy_scan_string(argv[1]);


    int token;
    while ((token = yylex()) != 0) {
        printf("-> %d\n", token);
        fflush(stdout);
    }
}
