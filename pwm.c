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
#include "pwm.h"

void pwm_init(void) {
	/* Don't touch the levels of the PWM output pins in this module. All
	 * direction/peripheral selection takes place in the h-bridge module. */

	/* Using crystal for timer clocking, set pins to osc peripheral */
	P2SEL |= 0xC0;

	/* Clear Timer B */
	TBCTL |= TBCLR;

	/* Select ACLK */
	TBCTL |= TBSSEL_ACLK;

	/* No pre-scaler */
	TBCTL |= ID_DIV1;

	/* Set the output mode of compare unit 1 and 2 */
	TBCCTL1 = TBCCTL2 = OUTMOD_RESET_SET;

	/* Set upper limit of timer count, allows up to 100 different speeds.
	 * Don't use 'full speed', i.e. constantly on, as the FET drivers
	 * require the high-side output to be changing. */
	TBCCR0 = PWM_MAX+1;

	/* Set initial speed */
	TBCCR1 = TBCCR2 = 0;

	/* Count up to TBCCR0 */
	TBCTL |= MC_UPTO_CCR0;
}

void pwm_set(pwm_ratio_t r) {
	TBCCR1 = r;
	/* LEDs connected to TB2, show motor power as brightness */
	TBCCR2 = r;
}

pwm_ratio_t pwm_get(void) {
	return TBCCR1;
}
