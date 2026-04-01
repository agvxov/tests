#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const char word_terminators[] = " \t\"'()";

bool is_not_termination(const char n, const char m){
	for(const char* i = word_terminators; *i != '\00'; i++){
		if(n == *i && m != '\\'){
			return false;
		}
	}
	return true;
}

void main(int argc, char* argv[]){
	const char* const str = argv[1];
	int size = strlen(argv[1]);
	int start = size - 1;
	while(is_not_termination(str[start], str[start-1])){
		if(start < 1){
			for(const char* i = word_terminators; *i != '\00'; i++){
				if(str[0] == *i){
					break;
				}
			}
			start--;
			break;
		}
		start--;
	}
	++start;
	if(str[start] == '\00'){ return; }
	fwrite(str+start, sizeof(char), size-start, stdout);
	return;
}
