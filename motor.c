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
#include "motor.h"
#include "pwm.h"
#include "h-bridge.h"

h_bridge_state_t old_state;

void motor_init(void) {
	h_bridge_set(M_OFF);
	motor_set(0);
}

void motor_set(int8_t power) {
	if (power > 0) {
		pwm_set(power);
		if (h_bridge_get() != M_BRAKE)
			h_bridge_set(M_FWD);
		else
			old_state = M_FWD;
	} else if (power < 0) {
		pwm_set(-power);
		if (h_bridge_get() != M_BRAKE)
			h_bridge_set(M_REV);
		else
			old_state = M_REV;
	} else {
		pwm_set(0);
		if (h_bridge_get() != M_BRAKE)
			h_bridge_set(M_OFF);
		else
			old_state = M_OFF;
	}
}

void motor_brake(bool on) {
	if (on) {
		old_state = h_bridge_get();
		h_bridge_set(M_BRAKE);
	} else {
		h_bridge_set(old_state);
	}
}
