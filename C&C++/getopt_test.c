#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, ";-a:")) != -1) {
        switch (opt) {
            default:
				printf("%c", opt);
                break;
        }
    }

    return 0;
}
