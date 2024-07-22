//gcc c_old_argument_notation.c -o c_old_argument_notation.out -O0 -ggdb
void f(c)
char *c;
{
	void* b = (void*)c;
}

signed main(){
	f("aaa");
}
