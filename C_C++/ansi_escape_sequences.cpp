#include <iostream>

using namespace std;

int main(){

	for(int i = 0; i < 25; i++){
		cout << i << " aslédh a" << (i + i * i - 1) / 1 << endl;
	}

	cout << "\33[2J" << "\33[;H" << "asd";
//	cout << "\33[;H" << "this is in the first line";

	return 0;
}
