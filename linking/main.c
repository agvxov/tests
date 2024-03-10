// @COMPILECMD gcc -shared i.c -o i.so; gcc -shared h.c -o h.so; gcc $@ i.so h.so
extern int  i;
extern int h;

signed main(){
	return h;
}
