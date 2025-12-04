// @BAKE spatch --sp-file $@ main.c -o main-patched.c
@ stub @
type T;
identifier F != main;
parameter list ps;
@@

+ extern
T
F ( ps )
- { ... }
+ ;

@ append @
identifier M = main;
identifier stub.F;
parameter list stub.ps;
@@

M ( ... ) {
++ (void)F;
    ...
}
