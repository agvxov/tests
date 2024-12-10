/* @BAKE
    flex -o string.yy.c $@
    gcc  -o string.out  string.yy.c -lfl
    ./string.out
   @STOP
 */
%{
	const char input_str[] = "This is my input";
    const int  len         = sizeof(input_str)-1;
          int  offset      = len;
    #define YY_INPUT(buf, result, max_size) {                        \
        int cpi = (offset && offset > max_size) ? max_size : offset; \
        memcpy(buf, input_str+(len-offset), cpi);                    \
        result = cpi;                                                \
        offset = (cpi > offset) ? 0 : offset - cpi;                  \
    }
%}
%%
%%
