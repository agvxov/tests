#include <xolatile/xtandard.c>
#include <xolatile/xyntax.c>

int main (int argc, char * * argv) {
	int index  = 0;
	int offset = 0;
	int length = 0;
	int select = 0;

	syntax_define (false, true, "Head",   "HCST.", '\\', colour_red,    effect_bold);
	syntax_define (false, true, "Circle", "HCST.", '\\', colour_green,  effect_bold);
	syntax_define (false, true, "Square", "HCST.", '\\', colour_yellow, effect_bold);
	syntax_define (false, true, "Tail",   "HCST.", '\\', colour_blue,   effect_bold);

	for (index = 1; index < argc; ++index) {
		char * input = argv [index];

		int count      = 0;
		int token [24] = { 0 };

		for (offset = 0; input [offset] != '\0'; offset += length) {

			select = syntax_select (& input [offset], & length);

			if (select >= syntax_count) {
				terminal_colour (colour_white, effect_normal);
			} else {
				terminal_colour (syntax_colour [select], syntax_effect [select]);
			}

			out (& input [offset], length);

			terminal_cancel ();

			if (string_compare_limit (& input [offset], "Head",   4) == true) token [count] = 1;
			if (string_compare_limit (& input [offset], "Circle", 6) == true) token [count] = 2;
			if (string_compare_limit (& input [offset], "Square", 6) == true) token [count] = 3;
			if (string_compare_limit (& input [offset], "Tail",   4) == true) token [count] = 4;

			++count;
		}

		echo (" -> ");
		for (offset = 0; offset < count - 1; ++offset) {
			if ((token [offset] == 1) && (token [offset + 1] == 2) && (token [offset + 2] == 4)) {
				echo ("1");
				offset += 2;
			} else if ((token [offset] == 1) && (token [offset + 1] == 3) && (token [offset + 2] == 4) && (token [offset + 3] == 3)) {
				echo ("3");
				offset += 3;
			} else if ((token [offset] == 1) && (token [offset + 1] == 3) && (token [offset + 2] == 4)) {
				echo ("2");
				offset += 2;
			} else {
				echo ("Invalid tokens...\n");
				return (log_failure);
			}
		}
		echo ("\n");
	}

	return (log_success);
}

