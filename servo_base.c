#include "servo_base.h"

void servoInitPwmTimer0(TC0_t *timer0, PORT_t *port, uint8_t pin)
{
	//Set output pins
	port->DIRSET = pin;
	//Single slope PWM
	timer0->CTRLB |= TC_WGMODE_SS_gc;
	
	if (pin & PIN0_bm)
		timer0->CTRLB |= TC0_CCAEN_bm;
	if (pin & PIN1_bm)
		timer0->CTRLB |= TC0_CCBEN_bm;
	if (pin & PIN2_bm)
		timer0->CTRLB |= TC0_CCCEN_bm;
	if (pin & PIN3_bm)
		timer0->CTRLB |= TC0_CCDEN_bm;
		
	timer0->PER = usToTicks(SERVO_DEF_PER, SERVO_PRESC);
	
	//Prescaler 256
	timer0->CTRLA |= TC_CLKSEL_DIV256_gc;
}

void servoInitPwmTimer1(TC1_t *timer1, PORT_t *port, uint8_t pin)
{
	//Set output pins
	port->DIRSET = pin;
	//Single slope PWM
	timer1->CTRLB |= TC_WGMODE_SS_gc;
	
	if (pin & PIN4_bm)
		timer1->CTRLB |= TC1_CCAEN_bm;
	if (pin & PIN5_bm)
		timer1->CTRLB |= TC1_CCBEN_bm;
	
	timer1->PER = usToTicks(SERVO_DEF_PER, SERVO_PRESC);
	
	//Prescaler 256	
	timer1->CTRLA |= TC_CLKSEL_DIV256_gc;
}

void servoSetPeriodTimer0(TC0_t *timer0, uint16_t period_us)
{
	timer0->PERBUF = usToTicks(period_us, SERVO_PRESC);
}

void servoSetPeriodTimer1(TC1_t *timer1, uint16_t period_us)
{
	timer1->PERBUF = usToTicks(period_us, SERVO_PRESC);
}

void servoSetWidthTimer0(TC0_t *timer0, uint8_t pin, uint16_t width_us)
{
	uint16_t ticks = usToTicks(width_us, SERVO_PRESC);
	
	if (pin & PIN0_bm)
		timer0->CCABUF = ticks;
	if (pin & PIN1_bm)
		timer0->CCBBUF = ticks;
	if (pin & PIN2_bm)
		timer0->CCCBUF = ticks;
	if (pin & PIN3_bm)
		timer0->CCDBUF = ticks;
}

void servoSetWidthTimer1(TC1_t *timer1, uint8_t pin, uint16_t width_us)
{
	uint16_t ticks = usToTicks(width_us, SERVO_PRESC);
	
	if (pin & PIN4_bm)
		timer1->CCABUF = ticks;
	if (pin & PIN5_bm)
		timer1->CCBBUF = ticks;
}