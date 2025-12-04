#include <iostream>
#include <stdio.h>

using namespace std;

signed main(){

	char* buffer = nullptr;
	long lenght;
	FILE* f = fopen("llll.cpp", "r");

	if(!f){ exit(1); }

	fseek(f, 0, SEEK_END);
	lenght = ftell(f) + 1;
	fseek(f, 0, SEEK_SET);
	buffer = (char*)malloc(lenght);
	if(!buffer){ exit(1); }
	fread(buffer, 1, lenght, f);
	fclose(f);
	buffer[lenght - 1] = '\00';
	
	cout << buffer << endl;

	return 0;
}
