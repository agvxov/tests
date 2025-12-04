// @BAKE g++ -o $*.out $@
#include <stdio.h>
#include <string>
using namespace std;
signed main(void) {
    string a;
    char * b = NULL;
    a += b;

    puts(a.c_str());

    return 0;
}
