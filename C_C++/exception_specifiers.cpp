#include <iostream>
#include <string>

using namespace std;

#define CH "asd"

void mookie_betts(string c) throw(invalid_argument) {
	int i = stoi(c);
}

int main(){
	try{
		mookie_betts(CH);
	} catch(invalid_argument ia){
		cout << "strike!" << endl;
	}
	return 0;
}
