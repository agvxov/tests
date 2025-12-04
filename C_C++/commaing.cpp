#include <iostream>
#include <assert.h>

int my_for(int x);

using namespace std;

signed main(){

	cout << my_for(30);

	return 0;
}

int my_for(int x){

	for(signed i = 0, x = 10; (cout << "hi\n") , i < 12 && x != -5; i++, x--){
		cout << "loopin' " << x << endl;
	}

	assert((("custom error message"),0));

	return x;
}
