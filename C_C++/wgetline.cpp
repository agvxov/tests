#include <iostream>
#include <fstream>
#include <string>
#include <memory>

using namespace std;

size_t wgetline(wifstream &f, wstring &str){
	const size_t step = 64;

	allocator<wchar_t> a;
	size_t next_free = 0;
	size_t asize = 0;
	wchar_t* c = NULL;

	do{
		if(not (next_free < asize)){
			c = a.allocate(asize + step, c);
			asize += step;
		}
		f.get(*(c + next_free));
		wcout << L":\"" << *(c + next_free) << L"\"\n";
		next_free++;
	}while( *(c + next_free - 1) != L'\n' );
	*(c + next_free - 1) = L'\00';

	str = c;
	a.deallocate(c, asize);

	return next_free - 1;
}

signed main(int argc, char* argv[]){
	setlocale(LC_ALL, "");

	//wifstream f("wgetline.txt");
	//wstring wstr;

	//wgetline(f, wstr);
	////wstr.clear();
	////wstr = L"¤a¤";
	//char w[] = "\xc2\xa4\x61\xc2\xa4";

	//
	//wcout << wstr << endl;

	cout << "¤aáúőűđĐ";

	//wcout << "\xa4\x61\xa4" << endl;
	//wcout <<  << endl;
	//wcout << "\xa4\xc2\x61\xa4\xc2" << endl;
	//printf("%s", (char*)wstr.c_str());

	return 0;
}


//#define W 2
//#if W == 1
//	#define STR_TYPE string
//	#define FSTREAM_TYPE ifstream
//	#define OUT cout
//#elif W == 2
//	#define STR_TYPE wstring
//	#define FSTREAM_TYPE wifstream
//	#define OUT wcout
//#endif
//
//using namespace std;
//
//signed main(int argc, char* argv[]){
//	//STR_TYPE s;
//	wchar_t s[256];
//	FSTREAM_TYPE f("wgetline.txt");
//
//	while(not f.eof()){
//		//getline(f, s, L'\n');
//		f.getline((wchar_t*)&s, 255, L'\n');
//		OUT << s << endl;
//	}
//
//	return 0;
//}

