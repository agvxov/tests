// @BAKE g++ -o $*.out $@
/* pretty sure this used to result in memory corruption, but it doesnt now
 */
#include <stack>

using namespace std;

signed main(void) {
    stack<int> my_stack;

    my_stack.push(1);
    my_stack.pop();

    my_stack.pop();

    return 0;
}
