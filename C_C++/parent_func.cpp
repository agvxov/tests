#include <iostream>

using namespace std;

class a{
	int asd = 0;
	public:
		void func(){
			cout << "Hi!" << endl;
		}

};

class b : public a {
	int basd = 1;
	public:
	b(){
		func();
	}
};

signed main(int argc, char* argv[]){

	b my_b;

	return 0;
}

