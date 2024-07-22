%{
    #include "main.tab.h"
    const char input_str[] = "HeadCircleTailHeadSquareTailHeadSquareTailSquare";
	const int  len         = sizeof(input_str)-1;
		  int  offset      = len;
	#define YY_INPUT(buf, result, max_size) {                        \
		int cpi = (offset && offset > max_size) ? max_size : offset; \
		memcpy(buf, input_str+(len-offset), cpi);                    \
		result = cpi;                                                \
		offset = (cpi > offset) ? 0 : offset - cpi;                  \
	}
%}
%option noyywrap
%%
Head        { return HEAD; }
Square      { return SQUARE; }
Circle      { return CIRCLE; }
Tail        { return TAIL; }
%%
