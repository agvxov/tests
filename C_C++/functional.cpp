#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

typedef void (*f)(int i);

const long long asd = 1;

struct alma{
    typedef long long mag;
    int m(){
    	return 42;
    }
} apple;

void a_what(int i){
    std::cout << "a what?";
}

int abs(int a){
    if(a > 0) return a;
    return a * -1;
}

int ten(){
    return 10;    
}

int main(){
    f idk = a_what;
    reference_wrapper<f> ss(idk);
    auto sa = std::cref(asd);
    auto abs_a = mem_fun(&alma::m);
    cout << abs_a(&apple);

	std::vector<int> v1 = { 99, 3, 6, 17, 31,};
    auto divisible_by_3 = [](int i){ if(i % 3 == 0){return 0;}else{return 1;} };
	int not_divisible =
        count_if(v1.begin(), v1.end(), not_fn(divisible_by_3));
    cout << "Elements not divisible by three: "
        << not_divisible << std::endl;
}
