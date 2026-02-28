// @BAKE gcc -D_XOPEN_SOURCE=500 -o $*.out $@ -std=c23
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

/* NOTE: Pointing out errors to Emil.
 */
int change_directory(char * filename) {
    char path[PATH_MAX], * terminator;
    if (!realpath(filename, path)
    ||  !(terminator = strrchr(path, '/'))) { return -1; }
    *terminator = '\0';
    // realpath()   == /home/anon/a
    // terminated() == /home/anon
    puts(path);
    return chdir(path);
}

signed main(void) {
    /* $ ls -l
     * drwxr-xr-x  2 anon anon    4.0K Feb 21 09:07  a/
     */
    return change_directory("a");
}
