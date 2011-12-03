#include <stdlib.h>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <cwiid.h>

int main()
{
	char buf[4];
	int count;
	cwiid_wiimote_t *wiimote = NULL;
	uint8_t ledstate = 0;
	uint8_t ledno;

	if ((wiimote = cwiid_open(BDADDR_ANY, 0)) == NULL) {
		fputs("Unable to connect", stderr);
		return EXIT_FAILURE;
	}
	fputs("connected", stdout);
	
	while ((count = read(0, buf, 4)))
	{
		if (buf[1] == ' ' && (buf[3] == '\n' || count == 3)) /* valid line */
		{
			ledno = buf[0] - 0x31;

			if (buf[2] == '1')
				ledstate |= (1 << ledno);
			else
				ledstate &= ~(1 << ledno);

			if (cwiid_set_led(wiimote, ledstate))
				fputs("Error setting LED state", stderr);
		}
	}
	return EXIT_SUCCESS;
}

