#include <iostream>

using namespace std;

class a{
    public:    
    int i, h;
    a(int _i, int _h){
        i = _i;
        h = _h;
    }
};

class b{
    public:    
    int z, y;
    b(int _z, int _y){
        z = _z;
        y = _y;
    }
};

int main()
{
    a* ao = new a(8, 2);
    b* bo = new b(2, 4);
    
    auto asd = reinterpret_cast<b*>(ao);
    
    cout << asd->z;

}
