#include <iostream>

using namespace std;

class mybitfield{
	public:
		char a : 4;
		//char b : 4;
	mybitfield(){
		a = 8;
		//b = 2;
	}

};

int main(){
	mybitfield ss;

	cout << (unsigned int)ss.a;

	return 0;
}
