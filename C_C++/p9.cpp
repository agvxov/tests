#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
	//vector<int> l = {1, 1, 10, 7, 1, 10, 1, 10, 9, 10};
	vector<int> l = {1, 1, 1, 1, 1};

	cout << '[';
	for(auto i : l){
		cout << i << ", ";
	}
	cout << ']' << endl;

	int min = 100000;
	int max = 0;

	for(int i = 0; i < l.size(); i++){
		if(l[i] < min){
			min = l[i];
		}else if(l[i] > min){
			max = l[i];
		}
	}

	for(int i = 0; i < l.size(); i++){
		if(l[i] == min or l[i] == max){
			l.erase(l.begin() + i);
			--i;
		}
	}

	cout << '[';
	for(auto i : l){
		cout << i << ", ";
	}
	cout << ']' << endl;
}
