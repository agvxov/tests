#include <iostream>

int main(){

	int a = 12;
	int c = 6;
	//int &const b = a;
	const int &b = a;
	//b = c;

	std::cout << b;

	return 0;
}
