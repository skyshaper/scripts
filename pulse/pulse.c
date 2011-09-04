/**
 * The official Skyshaper pulse time.
 * If you do not use this, you suck.
 *
 * Original code by guenther, minor changes by derf
 */

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

static const double pulse_len = 86.4;

int main(int argc, char **argv) {
	time_t time_raw;
	struct tm * tm_utc;
	struct tm tm_arg;

	memset(&tm_arg, 0, sizeof(tm_arg));

	if((argc == 3) && !strcmp(argv[1], "-d")) {
		if(sscanf(argv[2], "%2u:%2u:%2u",
				&tm_arg.tm_hour,
				&tm_arg.tm_min,
				&tm_arg.tm_sec) < 2) {

			fputs("Usage: pulse -d HH:MM[:SS]\n", stderr);
			return EXIT_FAILURE;
		}
		if((tm_arg.tm_hour > 23) ||
				(tm_arg.tm_min > 59) ||
				(tm_arg.tm_sec > 59)) {
			fputs("Invalid timestamp\n", stderr);
			return EXIT_FAILURE;
		}
		tm_utc = &tm_arg;
	} else if ((argc == 3) && !strcmp(argv[1], "-r")) {
		char * strtod_err;
		double time_pulse = strtod(argv[2], &strtod_err);

		if (strtod_err && (strtod_err[0] != '\0')) {
			printf(
				"pulse: strtod: Conversion error at '%s'\n",
				strtod_err
			);
			return EXIT_FAILURE;
		}
		if (time_pulse >= 1000.0) {
			fputs("Invalid pulse\n", stderr);
			return EXIT_FAILURE;
		}

		double as_hour = time_pulse * 24 / 1000;
		double as_minute = fmod(as_hour, 1.0) * 60;
		double as_second = fmod(as_minute, 1.0) * 60;

		printf(
			"%02.f:%02.f:%02.f\n",
			floor(as_hour), floor(as_minute), floor(as_second)
		);
		return EXIT_SUCCESS;
	} else {
		if(time(&time_raw) < 0) {
			perror("time");
			return EXIT_FAILURE;
		}

		/* Did I ever mention how much the time.h functions suck?
		 * gmtime actually returns a pointer to a _statically_
		 * allocated struct.
		 */
		tm_utc = gmtime(&time_raw);
	}

	uint64_t seconds_utc = ((((tm_utc->tm_hour*60)+tm_utc->tm_min)*60)+tm_utc->tm_sec);

	printf("%u\n", (unsigned)((double)seconds_utc / pulse_len));

	return EXIT_SUCCESS;
}
