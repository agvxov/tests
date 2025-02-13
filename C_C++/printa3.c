/* @BAKE
    gcc -o $*.out $@ -ggdb -std=c23
    ./$*.out
   @STOP
*/
#include <stdio.h>

typedef void * mynulltpye;

void print_int(int i) {
    printf("%d", i);
}

void print_long(long i) {
    printf("%ld", i);
}

void print_float(float i) {
    printf("%f", i);
}

void print_double(double i) {
    printf("%lf", i);
}

void print_str(const char * i) {
    printf("%s", i);
}

void print_ptr(void * i) {
    printf("%p", i);
}

struct mynulltype { void * x; };

static inline __attribute__((optimize(3)))
void noop([[ maybe_unused ]] const struct mynulltype i) { return; }

#define print_switch(t) _Generic(t \
        ,default: noop        \
        ,int:    print_int    \
        ,long:   print_long   \
        ,float:  print_float  \
        ,double: print_double \
        ,char*:  print_str    \
        ,void*:  print_ptr    \
    )(t)

#define big_guy(\
        _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16,\
        _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32,\
        _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,\
        _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64,\
        _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80,\
        _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96,\
        _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112,\
        _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127, \
        ...\
    ) \
        print_switch(_1); print_switch(_2); print_switch(_3); print_switch(_4); \
        print_switch(_5); print_switch(_6); print_switch(_7); print_switch(_8); \
        print_switch(_9); print_switch(_10); print_switch(_11); print_switch(_12); \
        print_switch(_13); print_switch(_14); print_switch(_15); print_switch(_16); \
        print_switch(_17); print_switch(_18); print_switch(_19); print_switch(_20); \
        print_switch(_21); print_switch(_22); print_switch(_23); print_switch(_24); \
        print_switch(_25); print_switch(_26); print_switch(_27); print_switch(_28); \
        print_switch(_29); print_switch(_30); print_switch(_31); print_switch(_32); \
        print_switch(_33); print_switch(_34); print_switch(_35); print_switch(_36); \
        print_switch(_37); print_switch(_38); print_switch(_39); print_switch(_40); \
        print_switch(_41); print_switch(_42); print_switch(_43); print_switch(_44); \
        print_switch(_45); print_switch(_46); print_switch(_47); print_switch(_48); \
        print_switch(_49); print_switch(_50); print_switch(_51); print_switch(_52); \
        print_switch(_53); print_switch(_54); print_switch(_55); print_switch(_56); \
        print_switch(_57); print_switch(_58); print_switch(_59); print_switch(_60); \
        print_switch(_61); print_switch(_62); print_switch(_63); print_switch(_64); \
        print_switch(_65); print_switch(_66); print_switch(_67); print_switch(_68); \
        print_switch(_69); print_switch(_70); print_switch(_71); print_switch(_72); \
        print_switch(_73); print_switch(_74); print_switch(_75); print_switch(_76); \
        print_switch(_77); print_switch(_78); print_switch(_79); print_switch(_80); \
        print_switch(_81); print_switch(_82); print_switch(_83); print_switch(_84); \
        print_switch(_85); print_switch(_86); print_switch(_87); print_switch(_88); \
        print_switch(_89); print_switch(_90); print_switch(_91); print_switch(_92); \
        print_switch(_93); print_switch(_94); print_switch(_95); print_switch(_96); \
        print_switch(_97); print_switch(_98); print_switch(_99); print_switch(_100); \
        print_switch(_101); print_switch(_102); print_switch(_103); print_switch(_104); \
        print_switch(_105); print_switch(_106); print_switch(_107); print_switch(_108); \
        print_switch(_109); print_switch(_110); print_switch(_111); print_switch(_112); \
        print_switch(_113); print_switch(_114); print_switch(_115); print_switch(_116); \
        print_switch(_117); print_switch(_118); print_switch(_119); print_switch(_120); \
        print_switch(_121); print_switch(_122); print_switch(_123); print_switch(_124); \
        print_switch(_125); print_switch(_126); print_switch(_127);

#define printa(...) big_guy(__VA_ARGS__, \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), \
    ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}), ((struct mynulltype){0}) \
)

signed main(void) {
    printa(
        "number: ", 25, "\n",
        "fractional number: ", 1.2345, "\n",
        "expression: ", (2.0 + 5) / 3, "\n"
    );

    char *s = "abc";
    void *p = main;
    long l = 1234567890123456789;
    printa(
        "string: ", s, "\n",
        "pointer: ", p, "\n",
        "long: ", l, "\n"
    );

    printa(10l, "\n");

    return 0;
}
