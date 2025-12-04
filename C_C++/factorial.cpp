#include <iostream>

using namespace std;

unsigned long long factorial(int num){
    int sum = 1;
    for(int i = 1; i <= num; i++){
        sum = sum * i;
    }

    return sum;
}

int main(){

    cout << factorial(3) << endl;
    cout << factorial(4) << endl;
    cout << factorial(5) << endl;
    cout << factorial(10) << endl;
    cout << factorial(28) << endl;

    return 0;
}