#ifndef __PWM_H
#define __PWM_H
#include <stdint.h>

#define PWM_MAX 100

/* Type for holding a PWM ratio */
typedef uint8_t pwm_ratio_t;

void pwm_init(void);

/* Set the PWM ratio */
void pwm_set(pwm_ratio_t);

/* Get the PWM ratio */
pwm_ratio_t pwm_get(void);

#endif /* __PWM_H */
