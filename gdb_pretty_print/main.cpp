// @COMPILECMD g++ $@ -ggdb
#include <string.h>
#include <string>

enum class Test {
	TURTLE,
	BADGER,
	QUOKA
};

class myString {
	char * a;
	Test t = Test::BADGER;

	public:
		myString(const char * const i) {
			a = (char *)malloc(strlen(i)+1);
			strcpy(a, i);
		}
};

signed main(){

	myString s("aasd");
	std::string r("aasd");

	return 0;
}
