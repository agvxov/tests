#include <iostream>

using namespace std;

template<typename T> void func(T a);

int main(){

	string ss = "o7";
	func<string>(ss);	

	return 0;
}

template<typename T> void func(T a){
	cout << a;
}
