// From @me7alix
/*
 * Expression-based pattern matching (switch-like construct).
 *
 * This macro set allows you to write a switch-style conditional
 * directly inside expressions, making it possible to return values
 * without introducing statements or temporary variables.
 *
 * Example:
 *
 * enum Kind kind = KIND_SOME;
 *
 * char *res =
 *     (match(kind),
 *          mis(KIND_SOME) mth("KIND_SOME")
 *          mis(KIND_NONE) mth("KIND_NONE")
 *                         mow("ERROR"));
 */

static size_t match_ptr = 0;
static int match_stack[32];
#define match(v) (match_stack[match_ptr++] = (v))
#define mis(v) ((v) == match_stack[match_ptr-1]) ?
#define mth(v) (match_ptr--, v) :
#define mow(v) (match_ptr--, v)
