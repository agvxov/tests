#include <iostream>
#include <vector>
#include <memory>

using namespace std;

int main(){

    vector<int, allocator<int>> a = {10, 11, 12, 13, 8};

    for(auto i : a){
        cout << i << endl;
    }

    int var;
    cin >> var;
    int array[var];

    for(int i = 0; i < var; i++){
        array[i] = i;
    }
    for(int i = 0; i < var; i++){
        cout << array[i] << ", ";
    }
    cout << endl;

    int* arr = new int[var];

    for(int i = 0; i < var; i++){
        arr[i] = i;
    }
    for(int i = 0; i < var; i++){
        cout << arr[i] << ", ";
    }
    cout << endl;

    return 0;
}