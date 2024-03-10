// @COMPILECMD gcc $@ -ggdb -O0
int * ii(){
	int i = 4;
	return &i;
}

int * hh(){
	int h = 8;
	const int * my_i = ii();
	return my_i;
}

void beast(){
	char b[] = "akjshaskldahdjsajssssssssssssssjjjjjjjjjjjjjaaaaaaaaaaaaaaaaassssssssssss";
}

signed main(){
	const int * k = hh();
	beast();
}
