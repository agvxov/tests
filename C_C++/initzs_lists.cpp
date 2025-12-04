#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

int main(){

    auto ilist = {10, 12, 14, 0};
    vector<int> myvec = ilist;

    for(auto it : myvec){
        cout << it << endl;
    }

    return 0;
}