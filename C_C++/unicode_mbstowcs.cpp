#include <iostream>

using namespace std;

signed main(int argc, char* argv[]){
	const size_t max = 1024;

	char u[] = "\xc2\xa4\xc3\xa1\xc5\x91\xc3\xba\xc5\xb1\xc3\xba\xc2\xa4\x0a";
	wchar_t w[max];

	mbstowcs(w, u, max);

	wcout << w << endl;

	return 0;
}

