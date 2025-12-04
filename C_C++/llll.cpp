#include <iostream>

using namespace std;

class asd{
    public:
        int &x;
        asd(int &x_) : x(x_){
        }
};

int main(){
    int i = 3;

    asd a(i);

    cout << a.x << endl;

    return 0;
}