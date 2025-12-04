//turns out its depracated
#include <iostream>

using namespace std;

int count = 1;

int main(){

#ifdef __GNUG__
	int a = 10;
	int b = 4;

	int d = a <? b;

	for(int i = 0; i < d; i++){
		cout << count << endl;
	}
#endif

	return 0;
}
