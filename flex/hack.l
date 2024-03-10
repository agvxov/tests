/* @BAKE
    flex -o edge.yy.c $@
    gcc edge.yy.c -o edge.out -lfl
    ./edge.out
   @STOP
*/
%x HILL
%%
          { puts("Let me help you, Sisyphus!"); goto top; }
<HILL>.   { top: puts("There you go!"); exit(0); }
%%
