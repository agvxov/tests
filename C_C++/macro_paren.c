// @BAKE gcc $@ -o $*.out
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define EN_Pin GPIO_PIN_6
typedef int uint16_t;
signed main() { return EN_Pin; }
