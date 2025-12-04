#include <iostream>
#include <string>

class alma{
    public:
    static int a;
    int b;
    };

int alma::a = 2;

int main()
{
 alma as;
 alma bs;
 std::cout << as.a << alma::a;
}
