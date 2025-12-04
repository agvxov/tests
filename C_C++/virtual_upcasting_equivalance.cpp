// Example program
#include <iostream>
#include <string>
                            class    Top{ public: int t; };
                            class   Left : virtual public Top { public: int l; };
int main()
{
    Left* t1 = new Left();
    Top* t2  = t1;
    if(t1 == t2){
        std::cout << "equal\n";
    }

    std::cout << '0';
}

