// @BAKE gcc -fsanitize=address -g3 $@ -o $*.out
#include <stdlib.h>

int main(void) {
  int * prt = (int*)malloc(sizeof(int));
  return 0;
}
