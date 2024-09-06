%{
    #include <stdio.h>
    #include <string.h>
    #include <tree_sitter/api.h>
    #include "tslex.h"
%}
%token UNDEF
%token<nodeval> FUNCTION
%union {
    TSNode nodeval;
}
%%
document
    : any
    ;

any
    : %empty
    | UNDEF any
    | FUNCTION any {
        printf("-- %s\n",
            ts_node_string($1)
        );

        char * s = "declarator";
        TSNode identifier = ts_node_child_by_field_name($1, s, strlen(s));

        if (ts_node_is_null(identifier)) {
            break;
        }

        printf("-- %.*s\n",
            ts_node_text_len(identifier),
            ts_node_text(identifier)
        );
    }
    ;
%%

signed main() {
    yyinit();
    yyparse();
    yydeinit();

    return 0;
}
