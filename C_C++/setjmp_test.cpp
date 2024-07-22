#include <stdio.h>
#include <setjmp.h>

void f(int* a, int* b){
	*a += 3;
	*b += 5;
}

signed main(){
	int* heap_var = new int(1);
	int stack_var = 2;

	jmp_buf buf;
	
	int j = setjmp(buf);

	printf("heap: %d\nstack: %d\n---\n", *heap_var, stack_var);

	if(j){
		return 0;
	}

	f(heap_var, &stack_var);

	longjmp(buf, 1);
}
