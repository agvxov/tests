#include <iostream>

int main(){
	//ive been using these sequences for 8 months now and now it turns out theres supposedly a *dark* attribute too?!
	std::cout << "my text" << std::endl;
	std::cout << "\33[2;37;40m" << "my darker text" << std::endl;		//wow there is
	std::cout << "\33[0m";
	std::cout << "\33[Am" << "I'm over writting myself" << std::endl;


	std::cout << "\33[0m";
}
