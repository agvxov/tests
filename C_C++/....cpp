#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#include <ccomplex>
#include <uchar.h>
#include <wctype.h>

using namespace std;

int h;
char16_t where;
wctrans_t name;
wctype_t name2;

void wa_luigi(unsigned int asd, /*char* hi,*/ ...){
	char* ss = (char*)0x41;
	va_list my_wa;
	for(int i = 0; i < 10; i++){
		h++;
		va_start(my_wa, asd);
		while(1){
			ss = va_arg(my_wa, char*);
			if(ss == NULL){
				break;
			}
			cout << ss;
		}
		va_end(my_wa);
		cout << endl;
	}
}

int main(){

 	wa_luigi(3, /*"hi",*/ "why ", "thats so ugly ", "but also kinda cool");

	return h;
}
