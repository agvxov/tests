#include <iostream>
#include <chrono>

using namespace std;

typedef chrono::duration<int, ratio<100, 1>> Durrr;

int main(){
    Durrr durr;

    chrono::time_point<chrono::system_clock, Durrr> tp;

    cout << tp.time_since_epoch().count();

    durr = chrono::duration_cast<Durrr>(tp.time_since_epoch());

    return 0;
}