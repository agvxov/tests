#include <iostream>
#include <functional>
#include <random>
#include <codecvt>

using namespace std;

int main(){
    ranlux48 randy;
    bernoulli_distribution bnard(0.5);
    auto dice = bind(bnard, randy);

    cout << dice();

    return 0;
}