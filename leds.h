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

#ifndef __LEDS_H
#define __LEDS_H

/* Debugging and SRIC activity LED next to MSP */
#define LED_DBG_OUT P4OUT
#define LED_DBG (1<<7)

/* Motor direction/speed LEDs next to motor camcon */
#define LED_M_FWD_OUT P4OUT
#define LED_M_FWD_SEL P4SEL
#define LED_M_FWD (1<<5)
#define LED_M_REV_OUT P4OUT
#define LED_M_REV_SEL P4SEL
#define LED_M_REV (1<<2)

/* Feedback LEDs */
#define LED_FB_0_OUT P1OUT
#define LED_FB_0 (1<<0)
#define LED_FB_1_OUT P1OUT
#define LED_FB_1 (1<<1)

#define LEDSP1 (LED_FB_0 | LED_FB_1)
#define LEDSP4 (LED_DBG | LED_M_FWD | LED_M_REV)


#define leds_init() do { P1OUT &= ~LEDSP1; P1DIR |= LEDSP1; \
                         P4OUT &= ~LEDSP4; P4DIR |= LEDSP4; } while(0)

#define __led_set(led_out, led, x) do { if (x) led_out |= led; \
                                        else   led_out &= ~led; } while(0)

#define __led_toggle(led_out, led) do { led_out ^= led; } while(0)

/* Use like: led_set(LED_FB_0, 1); */
#define led_set(led, x)  __led_set(led##_OUT, led, x)
#define dbg_set(x)       __led_set(LED_DBG_OUT, LED_DBG, x)

#define led_toggle(led)  __led_toggle(led##_OUT, led)
#define dbg_toggle()     __led_toggle(LED_DBG_OUT, LED_DBG)

/* Set the LED to show the PWM value or the normal GPIO value.
 * Only makes sense for the motor LEDs. */
#define led_pwm(led, pwm) do { if (pwm) led##_SEL |= led; \
                               else     led##_SEL &= ~led; } while(0)

#endif /* __LEDS_H */
