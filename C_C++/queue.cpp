#include <iostream>
#include <vector>
#include <queue>

using namespace std;

queue<int> a;

int main(){

    a.push(0);
    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    a.push(5);

    while(!a.empty()){
        cout << a.front() << ", ";
        a.pop();
    }
    cout << endl;

}