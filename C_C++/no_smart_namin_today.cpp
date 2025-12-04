#include <iostream>
#include <fstream>
#include <string>

using namespace std;

signed main(){
	//string h;

	//ifstream i;
	//i.open("the_kind_of_tired_sleep_cant_fix.cpp");
	//i >> h;
	//cout << h;
	//i.close();

	ifstream i;
	i.open("the_kind_of_tired_sleep_cant_fix.cpp");
	string h((istreambuf_iterator<char>(i)), (istreambuf_iterator<char>()));
	cout << h;
	i.close();

	return 0;
}
