#include <stdio.h>
#include <regex.h>

int main() {
    regex_t regex;

    regcomp(&regex, "(pattern) (example)", REG_EXTENDED);

    char test_str[] = "This is a pattern example.";
    regmatch_t pmatch[3]; // One for the whole match, and one for each group

    if (regexec(&regex, test_str, 3, pmatch, 0) == 0) {
        printf("Whole match: %.*s\n", pmatch[0].rm_eo - pmatch[0].rm_so, test_str + pmatch[0].rm_so);
        printf("Group 1: %.*s\n", pmatch[1].rm_eo - pmatch[1].rm_so, test_str + pmatch[1].rm_so);
        printf("Group 2: %.*s\n", pmatch[2].rm_eo - pmatch[2].rm_so, test_str + pmatch[2].rm_so);
    } else {
        printf("Pattern not found.\n");
    }

    regfree(&regex);

    return 0;
}
