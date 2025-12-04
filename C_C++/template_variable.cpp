#include <iostream>

class iint{
	public:
	int x;
	int y;

	void operator=( iint j){
		x = j.x;
		y = j.y;
	}

}i;

class boool{
	public:
	bool bb;
	bool bc;

	boool(bool b, bool c) : bb(b), bc(c){}

}b(1, 0);


template<typename T> T pi;
//template<> boool pi(bool b, bool c);
//template<typename U> U inf(U v);
template<typename V/*, typename W*/> V u = int(10);
 
template<class T>
T circular_area(T r)
{
    return pi<T> * r * r;
}

int main()
{
	i.x = 3;
	i.y = 14;
	pi<int> = 10;
	pi<float> = 3.14;
	pi<bool> = true;
	pi<iint> = i;
	//pi<boool>(1, 0);
	//inf<int>(10);
	//u<int*>;
    std::cout << pi<int> << ", " << pi<float> << ", " << pi<iint>.x << '.' << pi<iint>.y << ", " << u<long> << ", " << pi<bool>;
    return 0;
}
