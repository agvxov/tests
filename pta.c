// @COMPILECMD gcc $@ -o $*.out

signed main(){
	long a[] = {10, 11, 12};
	long * b = a;
	++b;
	return *b;
}
