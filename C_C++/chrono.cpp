#include <iostream>
#include <chrono>

using namespace std;

signed main(int argc, char* argv[]){
	auto i = std::chrono::high_resolution_clock::now().time_since_epoch();
	cout << chrono::duration_cast<chrono::milliseconds>(i).count() / 1000 << endl;
	cout << chrono::duration_cast<chrono::seconds>(i).count() << endl;

	return 0;
}

