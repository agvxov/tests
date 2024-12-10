#include <stdio.h>
#include "poller.h"

int print_poll_decision(const int yes, const int no){
	if (yes > no) {
		puts("The voters have decided on \033[32myes\033[0m.");
	} else {
		puts("The voters have decided on \033[31mno\033[0m.");
	}

	return 0;
}

int print_poller_status(const char * const question, const int yes, const int no, const int voter_max) {
	printf("\033[1m%s?\033[0m Yes: %d | No: %d\n", question, yes, no);
	if (is_majority(yes, no, voter_max)) {
		print_poll_decision(yes, no);
	}

	return 0;
}

signed main() {
	poller_display_status = print_poller_status;
	poller_display_decision = print_poll_decision;

	char * input = NULL;
	size_t lenght = 0;

	do{
		getline(&input, &lenght, stdin);
		poller_interpret(input);
	} while(1);

	return 0;
}
