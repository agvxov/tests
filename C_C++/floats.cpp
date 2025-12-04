#include <stdio.h>
#include <fenv.h>
#include <float.h>

auto u = FLT_MIN;

fenv_t ss;
fexcept_t sa;

int main(){
	float asd = 0b00111111100000000000000000000000;
	printf("%f\n", asd);
	printf("%f", u);
	;
}
