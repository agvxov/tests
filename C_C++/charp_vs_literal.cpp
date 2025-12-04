//g++ charp_vs_literal.cpp -o charp_vs_literal.out -g
#include <iostream>
#include <cstring>

using namespace std;

void func(const char* cmd){
	if(cmd == "AAAA"){ cout << "func\n"; }
}

void func1(const char* cmd){
	if(!strcmp(cmd, "AAAA")){ cout << "func1\n"; }
}

signed main(int argc, char* argv[]){
	string a;
	getline(cin, a);
	func(a.c_str());
	func1(a.c_str());
	return 0;
}

