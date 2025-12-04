
#include <iostream>

using namespace std;

class Crocodile{
	size_t length;
	size_t age;
	bool has_eaten_a_nigger;
	public:
		string is_number(){
			return "yes";
		}
};

signed main(int argc, char* argv[]){
	Crocodile* croc = new Crocodile();
	cout << *((int*)croc) << endl;

	return 0;
}

