#define _XOPEN_SOURCE_EXTENDED
#include <iostream>
#include <fstream>
#include <vector>
#include <locale.h>
#include <ncurses.h>
#include "utfcpp/source/utf8.h"

using namespace std;

signed main(int argc, char* argv[]){
	setlocale(LC_ALL, "");

	ifstream f("f.txt");
	vector<string> vs;
	string str;
	while(getline(f, str)){
		if(utf8::is_valid(str)){
			vs.push_back(str);
		}
	}

	vector<u32string> vws;
	for(auto i : vs){
		vws.push_back(utf8::utf8to32(i));
	}

	initscr();
	addwstr((wchar_t*)vws[3].c_str());
	refresh();
	while(true){}
	endwin();

	return 0;
}
