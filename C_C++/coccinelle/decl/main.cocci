virtual def
virtual decl
virtual find_decl

// -------
@ depends on def @
type T;
parameter list ps;
identifier F;
fresh identifier F_fn = F ## "_fn";
@@

- T F ( ps ) { ... }
+ T ( * F_fn ) ( ps );

// -------
@ depends on decl @
type T;
parameter list ps;
identifier F;
fresh identifier F_fn = F ## "_fn";
@@

- T F ( ps );
+ T ( * F_fn ) ( ps );

// -------
@ depends on find_decl @
type T;
parameter list ps;
identifier F;
@@

* T F ( ps );
