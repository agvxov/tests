// @BAKE gcc -o $*.out $@ $(pkg-config --cflags --libs criterion)
#include <criterion/criterion.h>

Test(simple, test) {
    cr_assert(0, "Hello World");
}
