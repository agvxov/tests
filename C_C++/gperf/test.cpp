/* @BAKE
    #gperf test.gperf
    g++ -x c++ -o $*.out $@ -std=c++23
    #gcc -x c -o $*.out $@ -std=c23 # nope, wont work
   @STOP
*/
#include <stddef.h>
#include <string.h>
#include "my_gperf.h"

#define hash(x) hash_(x, strlen(x))

signed main(void) {
    switch (hash("stop")) {
        case hash("stop"):  return 1;
        case hash("start"): return 0;
    }

    return 127;
}
