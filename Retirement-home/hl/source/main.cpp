#include <dictate.hpp>

#include "hl.h"

using namespace std;

extern "C" int source_vimhl(const char * filename);

#define READ_ENTIRE_FILE(filehandle, buffername) \
    fseek(filehandle, 0, SEEK_END); \
    int filehandle ## len = ftell(filehandle); \
    rewind(filehandle); \
    char buffername[filehandle ## len+1]; \
    buffername[filehandle ## len] = '\00'; \
    fread(buffername, filehandle ## len, sizeof(char), filehandle); \
    fclose(filehandle);

signed main(int argc, char * argv[]) {
    //source_vimhl("test/script.vim");
    source_vimhl("test/docker-compose.vim");

    const char * input_name = "test/input.txt";
    if (argc > 1) {
        input_name = argv[1];
    }

    FILE* f = fopen(input_name, "rw");
    if (!f) { return 1; }

    READ_ENTIRE_FILE(f, fstr);

    dictate(hl(fstr));

    freehl();

    return 0;
}
