%%
.   {
        putchar(yytext[0]);
    }
\n  {
        // do nothing
    }
%%
// this program removes new lines from the input and outputs it to STDOUT
/* @BAKE
    flex -o example.yy.c example.l
    gcc example.yy.c -lfl
   @STOP
    ^ NOTE: the BAKE comment is not part of flex, its just how you would compile this

    // simplest example i could come up with on the spot for this one ukrainian guy
*/
