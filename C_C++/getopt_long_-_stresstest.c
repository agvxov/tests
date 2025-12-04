// @BAKE gcc -o $*.out $@ -std=c23 -ldictate
#define _GNU_SOURCE
#include <string.h>
#include <getopt.h>
#include <dictate.h>

bool f = false;
char * p = "--";
char C = '-';

signed main(int argc, char * argv[]) {
    //struct option long_options[] = {
    //    { "flag",  no_argument,       NULL, 'f' },
    //    { "param", required_argument, NULL, 'p' },
    //    { 0, 0, 0, 0 },
    //};

    //int c;
    //while ((c = getopt_long(argc, argv, "fp:", long_options, NULL)) != -1) {
    //    switch (c) {
    //        case 'f': {
    //            f = true;
    //        } break;
    //        case 'p': {
    //            p = strdup(optarg);
    //        } break;
    //    }
    //}

    //dictate("f: ", f, "\n");
    //dictate("p: ", p, "\n");

    // ---------

    //struct option long_options[] = {
    //    { "ex",  no_argument, NULL, 'X' },
    //    { 0, 0, 0, 0 },
    //};

    //int c;
    //while ((c = getopt_long_only(argc, argv, "ex", long_options, NULL)) != -1) {
    //    switch (c) {
    //        case 'e': case 'x': case 'X': {
    //            C = c;
    //        } break;
    //    }
    //}

    //dictate("C: ", C, "\n");

    // ---------

    //struct option long_options[] = {
    //    { "p",  required_argument, NULL, 'p' },
    //    { 0, 0, 0, 0 },
    //};

    //int c;
    //while ((c = getopt_long(argc, argv, "p:", long_options, NULL)) != -1) {
    //    switch (c) {
    //        case 'p': {
    //            p = optarg;
    //        } break;
    //    }
    //}

    //dictate("p: ", p, "\n");

    // ---------

    struct option long_options[] = {
        { "exec",  required_argument, NULL, 'p' },
        { "execa", required_argument, NULL, 0 },
        { 0, 0, 0, 0 },
    };

    int c;
    while ((c = getopt_long(argc, argv, "p:", long_options, NULL)) != -1) {
        switch (c) {
            case 'p': {
                p = optarg;
            } break;
        }
    }

    dictate("p: ", p, "\n");

    return 0;
}
