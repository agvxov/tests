#include <stdio.h>
#include <regex.h>

int main() {
    regex_t regex;

    regcomp(&regex, "pattern", 0);

    char test_str[] = "This is a pattern example.";
    regmatch_t pmatch[1];

    if (regexec(&regex, test_str, 1, pmatch, 0) == 0) {
        printf("Pattern found at position %d.\n", pmatch[0].rm_so);
    } else {
        printf("Pattern not found.\n");
    }

    regfree(&regex);

    return 0;
}
