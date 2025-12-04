/* @BAKE
    spatch --sp-file $@ main2.c -o main-patched.c
    bake main-patched.c
   @STOP
*/
@ stub @
type T;
parameter list ps;
identifier F != { main, hot_init_, hot_rebind, has_changed };
fresh identifier F_fn = F ## "_fn";
@@

-T F ( ps ) { ... }
+T ( * F_fn )( ps );

@ indirect_call @
identifier stub.F;
identifier stub.F_fn;
@@

-F()
+F_fn()

//@ add @
//identifier M = main;
//position p;
//@@
//
//M ( ... ) { ... }
//+ void hot_reload(void) { ; }

@ open depends on add @
identifier R = hot_rebind;
@@

R ( ... ) {
+   REOPEN;
    ...
}

@ append @
identifier R = hot_rebind;
identifier stub.F;
identifier stub.F_fn;
@@

R ( ... ) {
    ...
++  F_fn = dlsym(handle, STRINGIFY(F));
++  if (! F_fn ) { ECHO_DL_ERROR; }
}
