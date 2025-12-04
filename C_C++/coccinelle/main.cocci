// @BAKE spatch --sp-file main.cocci main.c -o main-patched.c

// @ rename @
// 
// @@
// 
// - main()
// + f()

@ rename @
identifier F;
fresh identifier Fa = F ## "_asd";
@@

- F()
+ Fa()
