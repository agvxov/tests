// @BAKE gcc -o $*.out $@
/* Compatibility notes:
 *  - bitfield layout is implementation defined
 *  - binary literals are a C++/gcc extension
 *  - the following works on gcc amd64
 */

#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t mantissa : 23;
    uint32_t exponent : 8;
    uint32_t sign     : 1;
} IEEE754;

int main(void) {
    IEEE754 my_float = {
        .sign     = 0,
        .exponent = 0b10001001,
        .mantissa = 0b01111111001010000000000,
    };

    printf("%f\n", *(float*)&my_float);
}
