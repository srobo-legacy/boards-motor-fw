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
#include <signal.h>
#include <stddef.h>
#include "drivers/sched.h"
#include "drivers/usci.h"
#include "libsric/sric.h"

const usci_t usci_config[1] = {
	{
		.tx_gen_byte = sric_tx_cb,
		.rx_byte = sric_rx_cb,

		/* 115200 baud
		   from http://mspgcc.sourceforge.net/baudrate.html */
		.br0 = 0x8A,
		.br1 = 0x00,
		.mctl = 0xef,

		.sel_rx = &P3SEL,
		.sel_tx = &P3SEL,
		.sel_rx_num = 5,
		.sel_tx_num = 4,
	},
};

const sric_conf_t sric_conf = {
	.usart_tx_start = usci_tx_start,
	.usart_rx_gate = usci_rx_gate,
	.usart_n = 0,

	.rx_cmd = NULL,
	.rx_resp = NULL,
};

void init(void) {
	/* Set DCO to 16MHz */
	DCOCTL = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;

	sched_init();
	usci_init();

	sric_init();

	eint();
}

int main(void) {
	/* Disable watchdog */
	WDTCTL = WDTHOLD | WDTPW;

	init();

	while(1);
}
