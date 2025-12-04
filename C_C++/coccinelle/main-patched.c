/* @BAKE
    gcc -o $*.out $@ -std=c23 -ggdb
    gcc -fPIC -shared -o lib$@.so main2.c -std=c23 -ggdb
   @STOP
*/
#include "hot.h"

#include <stdio.h>
void(*h_fn)(void);
void(*f_fn)(void);

signed main(void) {
    hot_init(SO_NAME(__FILE__));

    while (true) {
        hot_rebind();

        h_fn();
        f_fn();
    }

    return 0;
}

void hot_reload(void)
{
    ;
}
