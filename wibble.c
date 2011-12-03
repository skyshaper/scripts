#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <bluetooth/bluetooth.h>
#include <cwiid.h>

#define MAX_BRIGHTNESS 10

cwiid_mesg_callback_t cwiid_callback;

volatile uint8_t cnt_max = 7;

int main()
{
	cwiid_wiimote_t *wiimote = NULL;

	struct cwiid_state state;

	uint8_t ledstate = 0x0f;

	uint8_t cnt = 0;
	uint8_t led[4] = {0, 0, 0, 0};

	uint8_t step = 0;
	uint8_t x = 0;
	uint8_t x_max = 19;

	uint8_t f_led[4][x_max];

	uint8_t i;

	if ((wiimote = cwiid_open(BDADDR_ANY, 0)) == NULL) {
		fputs("Unable to connect\n", stderr);
		return EXIT_FAILURE;
	}
	fputs("connected\n", stdout);

	sleep(2);

	for (i = 0; i < x_max; i++) {
		f_led[0][i] = floor( 5 * ( cos( (float) (i +  0) / 3 ) + 1 ) );
		f_led[1][i] = floor( 5 * ( cos( (float) (i +  3) / 3 ) + 1 ) );
		f_led[2][i] = floor( 5 * ( cos( (float) (i +  6) / 3 ) + 1 ) );
		f_led[3][i] = floor( 5 * ( cos( (float) (i +  9) / 3 ) + 1 ) );
	}

	if (!cwiid_get_state(wiimote, &state))
		printf("battery at %d%%\n",
			(int)(100.0 * state.battery / CWIID_BATTERY_MAX));

	if (cwiid_set_mesg_callback(wiimote, cwiid_callback))
		fputs("cannot set callback. buttons won't work.\n", stderr);
	
	if (cwiid_enable(wiimote, CWIID_FLAG_MESG_IFC))
		fputs("cannot enable callback. buttons won't work.\n", stderr);

	if (cwiid_set_rpt_mode(wiimote, CWIID_RPT_BTN | CWIID_RPT_STATUS))
		fputs("cannot set report mode. buttons won't work.\n", stderr);

	while (1) {

		if (++cnt == cnt_max) {
			cnt = 0;
			
			if (++x == x_max)
				x = 0;

			for (i = 0; i < 4; i++)
				led[i] = f_led[i][x];
		}

		step = cnt % MAX_BRIGHTNESS;

		if (step == 0)
			ledstate = 0x0f;

		for (i = 0; i < 4; i++)
			if (step == led[i])
				ledstate &= ~(1 << i);

		if (cwiid_set_led(wiimote, ledstate))
			fputs("Error setting LED state\n", stderr);
	}

	return EXIT_SUCCESS;
}

void cwiid_callback(cwiid_wiimote_t *wiimote, int mesg_count,
	union cwiid_mesg mesg[], struct timespec *timestamp)
{
	for (int i = 0; i < mesg_count; i++) {
		if (mesg[i].type == CWIID_MESG_BTN) {

			if (mesg[i].btn_mesg.buttons & 0x1000)
				cnt_max -= (cnt_max > 1 ? 1 : 0);
			if (mesg[i].btn_mesg.buttons & 0x0010)
				cnt_max += 1;
			if (mesg[i].btn_mesg.buttons & 0x0080) {
				exit(0);
			}

		}
	}
}

