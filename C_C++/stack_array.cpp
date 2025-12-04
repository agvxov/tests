#include <iostream>

using namespace std;

signed main(){
	int i;
	cin >> i;
	char a[i + 1];
	for(int h = 0; h < i; h++){
		a[h] = 'g';
	}
	a[i] = '\00';
	cout << a << endl;
}
