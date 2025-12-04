#include <iostream>

using namespace std;

class b{
	int a = 1;
	int b = 2;
	int c = 3;
};

signed main(int argc, char* argv[]){

	int i = 12;
	int h = 73;
	b barray[10];

	cout << boolalpha;
	cout << (int&)(*(barray + 1)) << endl;
	//cout << barray + barray << endl;
	cout << barray - barray << endl;
	cout << (barray+1 >= barray+2) << endl;
	cout << ((b*)0x0 <= barray+2) << endl;
	cout << &barray[0] << " : " << &barray[9] << endl;
	cout << &i << " : " << &h << endl;

	return 0;
}

