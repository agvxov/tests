#include <stdio.h>

int main(){

	int a = 10;
	int g = 14;
	int& b = a;
	//int& d = a + 3;
	int&& c = a + 2;
	printf("c: %p", &c);
	b = g;
	c = b;
	printf(" b: %p; c: %p", b, c);

	return a;
}
