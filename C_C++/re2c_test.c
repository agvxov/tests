/* @BAKE
    re2c -o $*.re.c $@ -i --case-ranges
    g++ -o $* $*.re.c
    ./$*
   @STOP
*/
#include <assert.h>

bool lex(const char *s) {
    const char *YYCURSOR = s;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;

        number = [1-9][0-9]*;

        number { return true; }
        *      { return false; }
    */
}

int main() {
    assert(lex("1a34"));
    return 0;
}
