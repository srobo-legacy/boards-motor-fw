/*   Copyright (C) 2010 Richard Barlow

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <io.h>
#include "h-bridge.h"

#define M_BL (1<<0)
#define M_TL (1<<4)
#define M_BR (1<<3)
#define M_TR (1<<1)

#define M_OUTPUTS (M_BL | M_TL | M_BR | M_TR)

static h_bridge_state_t state;

void h_bridge_init(void) {
	/* Set H-bridge to be off by default */
	h_bridge_set(M_OFF);

	P4OUT &= ~M_OUTPUTS;
	P4DIR |= M_OUTPUTS;
}

void h_bridge_set(h_bridge_state_t s) {
	/* All state changes first disable the PWM output then the
	 * low-side output. Enabling is done in reverse. */
	switch (s) {
	default:
	case M_OFF:
		/* Disable both high-side PWM FETs */
		P4SEL &= ~(M_TL | M_TR);
		/* Disable both low-side FETs */
		P4OUT &= ~(M_BL | M_BR);
		break;
	case M_FWD:
		/* Disable 'reverse' FETs */
		P4SEL &= ~M_TR;
		P4OUT &= ~M_BL;
		/* Enable 'forward' FETs */
		P4OUT |=  M_BR;
		P4SEL |=  M_TL;
		break;
	case M_REV:
		/* Disable 'forward' FETs */
		P4SEL &= ~M_TL;
		P4OUT &= ~M_BR;
		/* Enable 'reverse' FETs */
		P4OUT |=  M_BL;
		P4SEL |=  M_TR;
		break;
	case M_BRAKE:
		/* Disable both high-side PWM FETs */
		P4SEL &= ~(M_TL | M_TR);
		/* Enable both low-side FETs */
		P4OUT |= (M_BL | M_BR);
		break;
	}

	state = s;
}

h_bridge_state_t h_bridge_get(void) {
	return state;
}
