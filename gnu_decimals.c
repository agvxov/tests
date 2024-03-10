// @COMPILECMD gcc $@ -o $*.out
#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>
signed main() {
	_Decimal32 d = 1;
	for (int i = 0; i < sizeof(_Decimal32); i++) {
		char c = *( ((char *)(&d)) + i );
		for(int h = 0; h < 8; h++){
			fputs(((c & 0b10000000) ? "1" : "0"), stdout);
			c <<= 1;
		}
		fputs(".", stdout);
	}
	puts("");
}
