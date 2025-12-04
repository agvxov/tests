#include <iostream>
#include <stack>
#include <signal.h>

using namespace std;

bool init();
void myHandler(int a);
bool binit = init();

stack<int> s;		// create stack

signed main(int argc, char* argv[]){
	s.pop();								// pop, resulting in the stack having -1 elements;
	cout << boolalpha << s.empty() << endl; // meaning empty() thinks s has elements...

	cout << "The program keeps running as normal" << endl;

	cout << s.top() << endl;	// segfault, which could be expected
	// At this poing myHandler() gets called

	return 0;
}

void myHandler(int a){
	cout << "Segmentation fault recived." << endl;
	s.push(12);		// try to push back an element; THIS ALSO RESULTS IN A SEGFAULT
}

bool init(){
	signal(SIGSEGV, &myHandler);

	return true;
}

//	CONCLUSION:
//		if a stack with 0 elements is ever popped, it cannot ever be used again
//		it has become a time bomb
