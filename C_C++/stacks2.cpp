#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class A {
	public:
		int i = 10;
		double d = 0.5;
		void print(){
			cout << this << ": {" << i << ", " << d << "};\n";
		}
};

signed main(int argc, char* argv[]){
	vector<A> v;
	for(int i = 0; i < 10; i++){
		v.emplace_back();
		v.back().i -= i;
	}

	//for(auto i : v){
	//	i.print();
	//}

	stack<A*> s;
	for(int i = 0; i < 10; i++){
		//s.push(&v[i]);
		s.push(&v.back());
	}
	while(not s.empty()){
		s.top()->print();
		s.pop();
	}

	return 0;
}

