/* @BAKE
    g++ -o $*.out $@
    ./$*.out
   @STOP
*/


#include <string>
#include <vector>
#include <iostream>

using namespace std;

// in a lexer, code exactly akin to this converst "OVERVIEW" to lower case
//  for no apparent reason unless the string constructor is explicitly called on the element
vector<string> my_vector = {
    "OVERVIEW",
};

signed main(void) {
    for (const auto & i : my_vector) {
        cout << i << endl;
    }
    return 0;
}
