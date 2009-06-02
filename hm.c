/*
 * Copyright © 2009 by Daniel Friesel <derf@derf.homelinux.org>
 * Licence: WTFPL <http://sam.zoy.org/wtfpl>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARR_SIZE(arr) (sizeof((arr)) / sizeof(*(arr)))
#define PART_SIZE 128

int main (int argc, char **argv) {
	const char *mark[] = {"", ".", "..", "!", "…"};
	struct timespec ntime;
	int i, j;
	char start[PART_SIZE] = "";
	char middle[PART_SIZE] = "";
	char end[PART_SIZE] = "";
	char *argument;
	unsigned int length;
	unsigned int index = 0;

	if (argc >= 3) {
		strncpy(start, argv[1], PART_SIZE);
		strncpy(middle, argv[2], PART_SIZE);
		if (argc >= 4)
			strncpy(end, argv[3], PART_SIZE);
	} else {
		if (argc == 2)
			index = 1;
		length = strlen(argv[index]);
		if ((length > 1) && (length-1 < PART_SIZE)) {
			if ((index == 0) && (strrchr(argv[index], '/') != NULL)) {
				argument = strrchr(argv[index], '/') + 1;
				length = strlen(argument);
			} else {
				argument = argv[index];
			}
			strncpy(start, argument, length-1);
			start[length-1] = '\0';
			strcpy(middle, argument + length-1);
		}
	}

	if (clock_gettime(CLOCK_REALTIME, &ntime) == -1)
		perror("clock_gettime");

	srand(ntime.tv_nsec);
	for (i = 0; i <= (rand() % 2); i++) {
		fputs(start, stdout);
		for (j = 0; j <= (rand() % 4); j++) {
			fputs(middle, stdout);
		}
		fputs(end, stdout);
	}

	puts(mark[rand() % ARR_SIZE(mark)]);

	return EXIT_SUCCESS;
}
