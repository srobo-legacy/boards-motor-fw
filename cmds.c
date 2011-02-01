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

#include "cmds.h"
#include "motor.h"
#include "flash430/sric-flash.h"

/* Arguments:
 *   - int8: speed/direction; -100 to 100
 *   - bool: brake; true == on, false == off */
static uint8_t sric_set_motor(const sric_if_t *iface);
/* Report current motor state - response contains same data as arguments to
 * the set_motor command */
static uint8_t sric_get_state(const sric_if_t *iface);

const sric_cmd_t sric_commands[] = {
	{sric_set_motor},
	{sric_get_state},
	{sric_flashr_fw_ver},
	{sric_flashw_fw_chunk},
	{sric_flashr_fw_next},
	{sric_flashr_crc},
	{sric_flashw_confirm},
};

const uint8_t sric_cmd_num = sizeof(sric_commands) / sizeof(const sric_cmd_t);

static uint8_t sric_set_motor(const sric_if_t *iface) {
	int8_t speed = iface->rxbuf[SRIC_DATA + 1];
	bool brake = iface->rxbuf[SRIC_DATA + 2];
	motor_brake(brake);
	motor_set(speed);
	return 0;
}

static uint8_t sric_get_state(const sric_if_t *iface) {
	motor_get_state(&iface->txbuf[SRIC_DATA]);
	return 2;
}
