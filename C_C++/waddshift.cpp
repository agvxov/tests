#include <iostream>
#include <string.h>

using namespace std;

#define ADDSHIFT(p, str) {\
	memcpy(p, str, wcslen(str) * sizeof(str[0]));\
	p += wcslen(str);\
}

signed main(int argc, char* argv[]){
	wchar_t a[120];
	wchar_t* p = a;

	ADDSHIFT(p, L"aaa");
	ADDSHIFT(p, L"bbb");

	wcout << a << endl;

	return 0;
}

