#ifndef __MOTOR_H
#define __MOTOR_H
#include <stdbool.h>
#include <stdint.h>
#include "pwm.h"

#define MOTOR_MAX PWM_MAX
#define MOTOR_MIN (0-PWM_MAX)

void motor_init(void);

/* Pass a value between MOTOR_MIN and MOTOR_MAX to set the motor
 * power from full reverse to full forward */
void motor_set(int8_t power);

/* Brake the motor when 'on' is true.
 * Must turn brake off to re-active motor */
void motor_brake(bool on);

/* Report the current motor configuration in output - byte 0 contains the
 * current power setting, byte 1 is a boolean indicating whether the motor
 * is braking */
void motor_get_state(uint8_t *output);

#endif /* __MOTOR_H */
