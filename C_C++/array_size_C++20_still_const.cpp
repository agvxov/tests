//g++ array_size_C++20_still_const.cpp -o array_size_C++20_still_const.out -std=c++20 -g
#include <iostream>

using namespace std;

signed main(int argc, char* argv[]){

	int i;
	cin >> i;

	int h[i];

	for(int j = 0; j < i; j++){
		h[j] = j;
	}

	for(int j = 0; j < i; j++){
		cout << h[i - j - 1] << "; ";
	}

	cout << endl;

	return 0;
}

