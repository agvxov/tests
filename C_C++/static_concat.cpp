#include <iostream>

using namespace std;

signed main(){
	char* a = "static" "concat";
	cout << a << endl;

	//cout << typeid("literal9").name() << endl;
	//char* b = "static" " " "concat";
	//char* b = "static" + ' ';
	const char c[] = "what?";
	char* b = "no " c;
	cout << b << endl;

	return 0;
}
