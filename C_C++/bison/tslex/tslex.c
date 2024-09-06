#include <stdio.h>
#include <string.h>
#include <tree_sitter/api.h>

#include "main.tab.h"

extern const TSLanguage * tree_sitter_c(void);

TSParser * parser;
TSTree * tree;
TSTreeCursor cursor;

TSNode current_node;

const char * source_code = "int main() { return 0; }";

int yyinit() {
    parser = ts_parser_new();

    ts_parser_set_language(parser, tree_sitter_c());
    tree = ts_parser_parse_string(parser, NULL, source_code, strlen(source_code));
    cursor = ts_tree_cursor_new(ts_tree_root_node(tree));
    current_node = ts_tree_root_node(tree);
}

int yydeinit() {
    ts_tree_delete(tree);
    ts_parser_delete(parser);
    ts_tree_cursor_delete(&cursor);
}

#define RETURN(x) do {\
    r = x; \
    goto END; \
} while(0);

int yylex() {
    int r = UNDEF;

    static int end = 0; // XXX
    if (end) {
        return 0;
    }

    if (!strcmp("function_definition", ts_node_type(current_node))) {
        yylval.nodeval = current_node;
        RETURN(FUNCTION);
    }

  END:
    if (ts_tree_cursor_goto_first_child(&cursor)
    &&  ts_tree_cursor_goto_next_sibling(&cursor)
    &&  ts_tree_cursor_goto_parent(&cursor)) {
        end = 1;
    } 

    current_node = ts_tree_cursor_current_node(&cursor);
    return r;
}

void yyerror() {
    puts("error -- this should never happen");
}
