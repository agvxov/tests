#include <iostream>
#include <limits>

using namespace std;

int trow_nan(int i){
    if(i == 11){
        return numeric_limits<int>::quiet_NaN();
    }
    else
    {
        return 11;
    }
    
}

int main(){
    int i = trow_nan(11);

    cout << i << endl;

    return 0;
}