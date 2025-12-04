#include <iostream>
#include <ratio>

using namespace std;

int ss = 4;

void vonalzo(int v);

int main(){
	typedef ratio<1, 2> half;
	typedef ratio<1, 8>	eight;
	ratio<1, 3> thirth;
	ratio<1, 4> fourth;

	cout << half::num << '/' << half::den << endl;
	cout << thirth.num << '/' << thirth.den << endl;

	vonalzo(ss++);
	typedef ratio_add<half, eight> sum;
	typedef ratio_divide<decltype(thirth), decltype(fourth)> sum2;

	cout << sum::num << '/' << sum::den << endl;
	cout << (double)sum::num/sum::den << endl << endl;


	cout << sum2::num << '/' << sum2::den << endl;
	cout << (double)sum2::num/sum2::den << endl;

	return 0;
}

void vonalzo(int v){
	for(int i = 0; i < v; i++){
		cout << '-';
	}
	cout << endl;
}