// @COMPILECMD gcc $@ -lreadline -lhistory
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    using_history(); // Initialize history

    char *input;
    while ((input = readline("Enter your command: ")) != NULL) {
        if (input[0] != '\0') {
            add_history(input); // Add to history
            // Process and handle input here
            printf("You entered: %s\n", input);
        }
        free(input); // Free allocated memory
    }

    // Save history to a file (optional)
    write_history("history.txt");

    return 0;
}
