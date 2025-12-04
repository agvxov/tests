#include <iostream>

using namespace std;

bool first(){
	cout << "first\n";
	return 0;
}

bool second(){
	cout << "second\n";
	return 1;
}

bool one = first();

int main(){

	cout << "main\n";

	return 0;
}

bool two = second();
