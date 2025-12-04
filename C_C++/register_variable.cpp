#include <iostream>

using namespace std;

int main(){

	register int ss asm("rax");
	asm("xor %rax, %rax;"
		"mov $3, %rax;");

	for(int i = 0; i < 100; i++){
		ss = 3;
		cout << ss << endl;
	}

	return 0;
}
