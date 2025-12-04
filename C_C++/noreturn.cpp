#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

[[noreturn]] void hardwired_to_self_distruct();

signed main(){

	cout << "Arming the abort";

	for(int i = 0; i < 3; i++){
		this_thread::sleep_for(1s);
		cout << '.';
	}
	cout << endl;

	hardwired_to_self_distruct();

	cout << "the controll flow will never reach me";

	return 0;
}

[[noreturn]] void hardwired_to_self_distruct(){
	abort();
}
