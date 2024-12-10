#ifndef POLLER_H
#define POLLER_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static char* question = NULL;
static int vote_yes_count = 0;
static int vote_no_count = 0;
static int voter_max;

int (*poller_display_status)(const char * const question, const int yes, const int no, const int voter_max) = NULL;
int (*poller_display_decision)(const int yes, const int no) = NULL;

bool is_majority(const int a, const int b, const int max) {
	return (max && ((a > (max / 2)) || (b > (max / 2))));
}

int poller_interpret(const char * const s) {
	if(!s){
		return 0;
	}

	int separation = 0;
	while (s[separation] && (s[separation] != ' ')) {
		++separation;
	}

	if (!strncmp(s, "poll", separation - 1)) {
		if(s[separation] == '\n'){
			return 0;
		}

		int base = separation;
		bool has_max = false;

		while (s[separation] && (s[separation] != '\n')) {
			if (s[separation] == ';') {
				has_max = true;
				break;
			}
			++separation;
		}
		
		const int len = ((separation - 1) - (base + 1)) + 1;
		free(question);
		question = malloc(len);
		strncpy(question, s + base + 1, len);

		if (has_max) {
			sscanf(s + separation + 2, "%d", &voter_max);
		} else {
			voter_max = 0;
		}
	} else if (!strncmp(s, "poll_status", separation - 1)) {
		if(poller_display_status){
			poller_display_status(question, vote_yes_count, vote_no_count, voter_max);
		}
	} else if (!strncmp(s, "vote", separation - 1)) {
		switch (s[separation + 1]) {
			case 'y':
			case 'Y': {
				++vote_yes_count;
			} break;
			case 'n':
			case 'N': {
				--vote_yes_count;
			} break;
		}

		if (is_majority(vote_yes_count, vote_no_count, voter_max) && poller_display_decision) {
			poller_display_decision(vote_yes_count, vote_no_count);
		}
	}

	return 1;
}

#endif
