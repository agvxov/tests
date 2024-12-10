// @BAKE gcc -E $@

//#define STR2(x) #x
//#define STRINGIZE(x) STR2(x)

#define STRINGIZE(x) #x

#define VERSION 1.0

const char* version_string = STRINGIZE(VERSION);
