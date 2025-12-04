// @BAKE gcc -o $*.out $@ -std=c23 -ldictate -ggdb
#include "list.h"
#include <dictate.h>

signed main(void) {
    list_t(int) my_list;
    init(my_list);

    push(int, my_list, 1);
    push(int, my_list, 2);
    push(int, my_list, 3);
    push(int, my_list, 4);
    push(int, my_list, 5);

    for (iter_t(int) i = begin(my_list); i; i = next(my_list, i)) {
        //dictate(i->p, " ", i->n, "\n");
        if (d(i) == 3) {
            remove_(my_list, i);
        }
    }

    for (iter_t(int) i = begin(my_list); i; i = next(my_list, i)) {
        dictatef("%d, ", d(i));
    }
    
    return 0;
}
