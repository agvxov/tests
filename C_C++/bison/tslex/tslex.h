#include <tree_sitter/api.h>

extern void yyerror();
extern int yyinit();
extern int yydeinit();
extern int yylex();

extern const char * source_code;

const char * ts_node_text(const TSNode node) {
    return source_code + ts_node_start_byte(node);
}

int ts_node_text_len(const TSNode node) {
    return ts_node_end_byte(node) - ts_node_start_byte(node);
}
