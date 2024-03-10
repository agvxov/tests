// @BAKE g++ $@ -o $*.cgi
#include <stdio.h>

signed main(int argc, char * * argv, char * * envp) {
	fputs("Content-Type: text/plain\r\n\r\n", stdout);
	fputs("hello world", stdout);
	return 0;
}
