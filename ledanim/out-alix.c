/* Copyright (c) 2008 Lars Stoltenow <penma@penma.de> */
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char buf[4];
	int count;
	int ledfd[3];
	
	ledfd[0] = open("/dev/.led/1", O_WRONLY);
	ledfd[1] = open("/dev/.led/2", O_WRONLY);
	ledfd[2] = open("/dev/.led/3", O_WRONLY);
	
	while (count = read(0, buf, 4))
	{
		if (buf[1] == ' ' && (buf[3] == '\n' || count == 3)) /* valid line */
		{
			if (buf[0] == '1' || buf[0] == '2' || buf[0] == '3') /* valid led */
			{
				if (buf[2] == '0' || buf[2] == '1') /* valid state */
				{
					buf[2] -= 47;
					buf[2] %= 2;
					buf[2] += 48;
					write(ledfd[buf[0] - 49], buf + 2, 1);
				}
			}
		}
	}
}

