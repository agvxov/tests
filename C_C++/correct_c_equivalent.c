// @BAKE gcc -O3 $@ -o $*.out
signed main() {
    const char message[] = "Hello, World!";
    const int message_len = sizeof(message)-1;
    const int repeat_count = 1000000;
    char * const buffer = malloc((repeat_count * message_len) + 1);

    for (int i = 0; i < repeat_count; i++) {
        memcpy(buffer + (message_len * i), message, message_len);
    }
    buffer[message_len * repeat_count] = '\0';

    puts(buffer);
}
/*
	signed main() {
		for (int i = 0; i < 1000000; i++) {
			printf("Hello, World!");
		}
	}
*/
