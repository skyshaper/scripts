/*
 * Copyright (C) 2011 by Daniel Friesel <derf@finalrewind.org>
 * License: WTFPL <http://sam.zoy.org/wtfpl>
 *   0. You just DO WHAT THE FUCK YOU WANT TO.
 */

/*
 * wibble: interactive wiimote blinkenlights with wobble.
 *
 * Usage: start wibble, put wiimote in discoverable mode, see blinkenlights
 *
 * Controls:
 *    D-Pad Up     toggle auto / manual mode
 *    D-Pad Left   previous animation
 *    D-Pad Right  next animation
 *    D-Pad Down   toggle rumble
 *
 *    -            decrease animation speed
 *    +            increase animation speed
 *
 *    Home         quit
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <bluetooth/bluetooth.h>
#include <cwiid.h>

#define MAX_BRIGHTNESS 10
#define X_MAX 19

cwiid_mesg_callback_t cwiid_callback;

volatile char rumble = 0;
volatile char auto_rumble = 1;

volatile char auto_mode = 1;
volatile int  cur_mode = 0;

volatile int8_t cnt_max = 7;
volatile uint8_t f_led[4][X_MAX];

const uint8_t stevens_io[19] = {
	0, 0, 1, 1, 1, 3, 5, 7, 9, 10, 9, 7, 5, 3, 1, 1, 1, 0, 0
};

void set_led_fun(int new_mode)
{
	const int max_current = 2;
	int i;

	cur_mode = new_mode;
	if (cur_mode < 0)
		cur_mode = max_current;
	else if (cur_mode > max_current)
		cur_mode = 0;

	switch (cur_mode) {
	case 0:
		for (i = 0; i < X_MAX; i++) {
			f_led[0][i] = floor( 5 * ( cos( (float) (i +  0) / 3 ) + 1 ) );
			f_led[1][i] = floor( 5 * ( cos( (float) (i +  3) / 3 ) + 1 ) );
			f_led[2][i] = floor( 5 * ( cos( (float) (i +  6) / 3 ) + 1 ) );
			f_led[3][i] = floor( 5 * ( cos( (float) (i +  9) / 3 ) + 1 ) );
		}
		break;
	case 1:
		for (i = 0; i < X_MAX; i++) {
			f_led[0][i] = floor( 5 * ( cos( (float) (i +  9) / 3 ) + 1 ) );
			f_led[1][i] = floor( 5 * ( cos( (float) (i +  6) / 3 ) + 1 ) );
			f_led[2][i] = floor( 5 * ( cos( (float) (i +  3) / 3 ) + 1 ) );
			f_led[3][i] = floor( 5 * ( cos( (float) (i +  0) / 3 ) + 1 ) );
		}
		break;
	case 2:
		for (i = 0; i < X_MAX; i++)
			f_led[0][i] = f_led[1][i] = f_led[2][i] = f_led[3][i]
				= stevens_io[i];
		break;
	}
}

int main()
{
	cwiid_wiimote_t *wiimote = NULL;

	struct cwiid_state state;

	uint8_t ledstate = 0x0f;

	uint8_t cnt = 0;
	uint8_t led[4] = {0, 0, 0, 0};

	uint8_t step = 0;
	uint8_t x = 0;

	uint8_t i;

	if ((wiimote = cwiid_open(BDADDR_ANY, 0)) == NULL) {
		fputs("Unable to connect\n", stderr);
		return EXIT_FAILURE;
	}
	fputs("connected\n", stdout);

	sleep(2);

	set_led_fun(0);

	if (!cwiid_get_state(wiimote, &state))
		printf("battery at %d%%\n",
			(int)(100.0 * state.battery / CWIID_BATTERY_MAX));

	if (cwiid_set_mesg_callback(wiimote, cwiid_callback))
		fputs("cannot set callback. buttons won't work.\n", stderr);
	
	if (cwiid_enable(wiimote, CWIID_FLAG_MESG_IFC))
		fputs("cannot enable callback. buttons won't work.\n", stderr);

	if (cwiid_set_rpt_mode(wiimote,
			CWIID_RPT_BTN | CWIID_RPT_ACC | CWIID_RPT_STATUS))
		fputs("cannot set report mode. buttons won't work.\n", stderr);

	while (1) {

		if (++cnt >= cnt_max) {
			cnt = 0;
			
			if (++x == X_MAX)
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

/* 97 .. 122 .. 150 */

void cwiid_callback(cwiid_wiimote_t *wiimote, int mesg_count,
	union cwiid_mesg mesg[], struct timespec *timestamp)
{
	for (int i = 0; i < mesg_count; i++) {
		if (mesg[i].type == CWIID_MESG_BTN) {

			if (mesg[i].btn_mesg.buttons & 0x0100)
				set_led_fun(cur_mode - 1);
			if (mesg[i].btn_mesg.buttons & 0x0200)
				set_led_fun(cur_mode + 1);
			if (mesg[i].btn_mesg.buttons & 0x1000)
				cnt_max -= (cnt_max > 1 ? 1 : 0);
			if (mesg[i].btn_mesg.buttons & 0x0010)
				cnt_max += 1;
			if (mesg[i].btn_mesg.buttons & 0x0800)
				auto_mode = !auto_mode;

			if (mesg[i].btn_mesg.buttons & 0x0400) {
				if (auto_mode)
					auto_rumble = !auto_rumble;
				else if (!rumble)
					cwiid_set_rumble(wiimote, (rumble = 1));
			}
			else if (rumble && !auto_mode)
				cwiid_set_rumble(wiimote, (rumble = 0));

			if (mesg[i].btn_mesg.buttons & 0x0080) {
				exit(0);
			}

		}
		else if ((mesg[i].type == CWIID_MESG_ACC) && auto_mode) {

			if (auto_rumble
					&& ((mesg[i].acc_mesg.acc[CWIID_X] < 90)
					||  (mesg[i].acc_mesg.acc[CWIID_X] > 155)
					||  (mesg[i].acc_mesg.acc[CWIID_Y] < 90)
					||  (mesg[i].acc_mesg.acc[CWIID_Y] > 155)
					||  (mesg[i].acc_mesg.acc[CWIID_Z] < 90)
					||  (mesg[i].acc_mesg.acc[CWIID_Z] > 155)))
			{
				if (!rumble)
					cwiid_set_rumble(wiimote, (rumble = 1));
			}
			else {
				if (rumble)
					cwiid_set_rumble(wiimote, (rumble = 0));
			}

			if (mesg[i].acc_mesg.acc[CWIID_X] < 123) {

				if (cur_mode != 0)
					set_led_fun(0);

				cnt_max = (mesg[i].acc_mesg.acc[CWIID_X] - 95) / 2;
				if (cnt_max < 2)
					cnt_max = 2;
			}
			else {

				if (cur_mode != 1)
					set_led_fun(1);

				cnt_max = (150 - mesg[i].acc_mesg.acc[CWIID_X]) / 2;
				if (cnt_max < 2)
					cnt_max = 2;
			}
		}
	}
}

