// @COMPILECMD gcc $@ -o $*.out
signed main(){
	char a = 'a';
	char b = 'b';
	const char * const p = &a;
	//*p = 'c';
	//p = &b;
}
