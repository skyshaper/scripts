/*
 * Converts lowercase chars into wide Unicode equivalent
 *
 * Copyright (C) 2008 by Lars Stoltenow <penma@penma.de>
 *                   and Daniel Friesel <derf@derf.homelinux.org>
 *
 * License: WTFPL <http://sam.zoy.org/wtfpl>
 */
#include <stdio.h>

int main()
{
	while (!feof(stdin))
	{
		int i = fgetc(stdin);
		int magic = ((i >> 5) + 1) >> 2;
		if ((i >= 33) && (i <= 126))
		{
			fputc(0xef, stdout);
			fputc(0xbc + magic, stdout);
			fputc(i + 0x60 - (magic << 6), stdout);
		}
		else if (i != EOF)
		{
			fputc(i, stdout);
		}
	}
}

