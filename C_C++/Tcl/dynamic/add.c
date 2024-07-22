// @BAKE tcc -shared -o add.so $@
//#include <tcc4tcl.h>
int add(int a, int b) {
    return a + b;
}
