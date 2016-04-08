#ifndef servo_base_h
#define servo_base_h

#include <avr/io.h>
#include "utils.h"

#define SERVO_DEF_PER			20000U
#define SERVO_DEF_MIN_PULSE_US	500
#define SERVO_DEF_MAX_PULSE_US	2500
#define SERVO_PRESC				256

//Any 8-bit bitmask can be used as 'pin' argument:
void servoInitPwmTimer0(TC0_t *timer0, PORT_t *port, uint8_t pin);
void servoInitPwmTimer1(TC1_t *timer1, PORT_t *port, uint8_t pin);

void servoSetPeriodTimer0(TC0_t *timer0, uint16_t period_us);
void servoSetPeriodTimer1(TC1_t *timer1, uint16_t period_us);

void servoSetWidthTimer0(TC0_t *timer0, uint8_t pin, uint16_t width_us);
void servoSetWidthTimer1(TC1_t *timer1, uint8_t pin, uint16_t width_us);
#endif