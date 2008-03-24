#include <stdio.h>

int main()
{
	while (!feof(stdin))
	{
		char i = fgetc(stdin);
		if ((i >= 32) && (i <= 128))
		{
			fputc(0xef, stdout);
			fputc(0xbc | (i >> 6), stdout);
			fputc(i + 0x20, stdout);
		}
	}
}

// Written by penma

