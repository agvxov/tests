#include <stdio.h>

void main(){
	char* i;
	asprintf(&i, "[%*s]\n", 10, "test");
	puts(i);
}
