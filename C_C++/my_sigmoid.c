/* @BAKE
    clear
    gcc main.c -lm
    ./a.out
   @STOP
 */
#include <math.h>
#include <stdio.h>
float my_sigmoid(float x) {
    float k = 80.0;
    float m = 0.5;

    return 1.0 / (1.0 + exp(-k * (x - m)));
}

float mixf(float a, float b, float t) {
    return a * (1.0f - t) + b * t;
}

signed main(void) {
    float step = 1.0 / 100.0;
    for (float i = 0.0; i < 1.0; i += step) {
        printf("%f :  %f - %f\n", i, my_sigmoid(i), mixf(0.55, 1.0, my_sigmoid(i)));
    }
    return 0;
}
