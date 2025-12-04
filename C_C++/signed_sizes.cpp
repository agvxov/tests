// @BAKE g++ -o $*.out $@ -Wall -Wpedantic
#include <iostream>
using namespace std;
signed main(void) {
    unsigned u1 = -2; // this doest warn !!!
    unsigned u2 = -4;
    cout << is_signed<decltype(u1-u2)>::value << " " << u1-u2 << "\n";
    cout << is_signed<decltype(u2-u1)>::value << " " << u2-u1 << "\n";
}
