#include <iostream>

using namespace std;

template<typename T> void swap(T&& t1, T&& t2){
	T swp = t1;
	t1 = t2;
	t2 = swp;
}

signed main(){
	int a = 10;
	int b = 12;
	swap(a, b);
	cout << a << "; " << b << endl;
}
