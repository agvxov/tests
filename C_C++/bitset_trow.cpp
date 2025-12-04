#include <iostream>
#include <bitset>

using namespace std;

void as(bitset<16> asd){
    for(int i = 0; i < asd.size(); i++){
        cout << asd[i];
    }    
}

int main()
{
    bitset<16> a("00a0110100011010");
    as(a);
}
