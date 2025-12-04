#include <iostream>

using namespace std;

[[ nodicard ]] int return1(){ return 1; }

signed main(int argc, char* argv[]){
	return 1 + return1();
}

