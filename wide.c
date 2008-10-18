/*
 * Converts lowercase chars into wide Unicode equivalent
 *
 * Written by penma
 *
 * [Ignores everything but lowercase chars, because the rest does not work]
 */
#include <stdio.h>

int main()
{
	while (!feof(stdin))
	{
		unsigned char i = fgetc(stdin);
		if ((i >= 97) && (i <= 122))
		{
			fputc(0xef, stdout);
			fputc(0xbc | (i >> 6), stdout);
			fputc(i + 0x20, stdout);
		}
	}
}

