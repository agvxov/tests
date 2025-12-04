#include <iostream>

using namespace std;

signed main(int argc, char* argv[]){

	try{
		throw 1;
	}catch(...){
		cout << "I" << endl;
		break;
		cout << "O" << endl;
	}

	return 0;
}

