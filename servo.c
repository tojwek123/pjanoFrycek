#include "servo.h"

void servoAttach(uint8_t servoNo, uint8_t pos)
{
	switch (servoNo)
	{
		case 0:
			servoData[0].timer0 = &TCC0;
			servoData[0].timer1 = NULL;
			servoData[0].port = &PORTC;
			servoData[0].pin = PIN0_bm;
			servoData[0].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[0].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[0].pos = pos;
			servoInitPwmTimer0(&TCC0, &PORTC, PIN0_bm);
			break;
		case 1:
			servoData[1].timer0 = &TCC0;
			servoData[1].timer1 = NULL;
			servoData[1].port = &PORTC;
			servoData[1].pin = PIN1_bm;
			servoData[1].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[1].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[1].pos = pos;
			servoInitPwmTimer0(&TCC0, &PORTC, PIN1_bm);
			break;
		case 2:
			servoData[2].timer0 = &TCC0;
			servoData[2].timer1 = NULL;
			servoData[2].port = &PORTC;
			servoData[2].pin = PIN2_bm;
			servoData[2].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[2].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[2].pos = pos;
			servoInitPwmTimer0(&TCC0, &PORTC, PIN2_bm);
			break;
		case 3:
			servoData[3].timer0 = &TCC0;
			servoData[3].timer1 = NULL;
			servoData[3].port = &PORTC;
			servoData[3].pin = PIN3_bm;
			servoData[3].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[3].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[3].pos = pos;
			servoInitPwmTimer0(&TCC0, &PORTC, PIN3_bm);
			break;
		case 4:
			servoData[4].timer0 = NULL;
			servoData[4].timer1 = &TCC1;
			servoData[4].port = &PORTC;
			servoData[4].pin = PIN4_bm;
			servoData[4].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[4].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[4].pos = pos;
			servoInitPwmTimer1(&TCC1, &PORTC, PIN4_bm);
			break;
		case 5:
			servoData[5].timer0 = NULL;
			servoData[5].timer1 = &TCC1;
			servoData[5].port = &PORTC;
			servoData[5].pin = PIN5_bm;
			servoData[5].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[5].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[5].pos = pos;
			servoInitPwmTimer1(&TCC1, &PORTC, PIN5_bm);
			break;
		case 6:
			servoData[6].timer0 = &TCD0;
			servoData[6].timer1 = NULL;
			servoData[6].port = &PORTD;
			servoData[6].pin = PIN0_bm;
			servoData[6].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[6].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[6].pos = pos;
			servoInitPwmTimer0(&TCD0, &PORTD, PIN0_bm);
		case 7:
			servoData[7].timer0 = &TCD0;
			servoData[7].timer1 = NULL;
			servoData[7].port = &PORTD;
			servoData[7].pin = PIN1_bm;
			servoData[7].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[7].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[7].pos = pos;
			servoInitPwmTimer0(&TCD0, &PORTD, PIN1_bm);
			break;
		case 8:
			servoData[8].timer0 = &TCD0;
			servoData[8].timer1 = NULL;
			servoData[8].port = &PORTD;
			servoData[8].pin = PIN2_bm;
			servoData[8].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[8].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[8].pos = pos;
			servoInitPwmTimer0(&TCD0, &PORTD, PIN2_bm);
			break;
		case 9:
			servoData[9].timer0 = &TCD0;
			servoData[9].timer1 = NULL;
			servoData[9].port = &PORTD;
			servoData[9].pin = PIN3_bm;
			servoData[9].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[9].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[9].pos = pos;
			servoInitPwmTimer0(&TCD0, &PORTD, PIN3_bm);
			break;
		case 10:
			servoData[10].timer0 = &TCE0;
			servoData[10].timer1 = NULL;
			servoData[10].port = &PORTE;
			servoData[10].pin = PIN0_bm;
			servoData[10].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[10].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[10].pos = pos;
			servoInitPwmTimer0(&TCE0, &PORTE, PIN0_bm);
			break;
		case 11:
			servoData[11].timer0 = &TCE0;
			servoData[11].timer1 = NULL;
			servoData[11].port = &PORTE;
			servoData[11].pin = PIN1_bm;
			servoData[11].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[11].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[11].pos = pos;
			servoInitPwmTimer0(&TCE0, &PORTE, PIN1_bm);
			break;
		case 12:
			servoData[12].timer0 = &TCE0;
			servoData[12].timer1 = NULL;
			servoData[12].port = &PORTE;
			servoData[12].pin = PIN2_bm;
			servoData[12].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[12].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[12].pos = pos;
			servoInitPwmTimer0(&TCE0, &PORTE, PIN2_bm);
			break;
		case 13:
			servoData[13].timer0 = &TCC0;
			servoData[13].timer1 = NULL;
			servoData[13].port = &PORTE;
			servoData[13].pin = PIN3_bm;
			servoData[13].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[13].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[13].pos = pos;
			servoInitPwmTimer0(&TCE0, &PORTE, PIN3_bm);
			break;
		case 14:
			servoData[14].timer0 = NULL;
			servoData[14].timer1 = &TCE1;
			servoData[14].port = &PORTE;
			servoData[14].pin = PIN4_bm;
			servoData[14].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[14].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[14].pos = pos;
			servoInitPwmTimer1(&TCE1, &PORTE, PIN4_bm);
			break;
		case 15:
			servoData[15].timer0 = NULL;
			servoData[15].timer1 = &TCE1;
			servoData[15].port = &PORTE;
			servoData[15].pin = PIN5_bm;
			servoData[15].minPulse = SERVO_DEF_MIN_PULSE_US;
			servoData[15].maxPulse = SERVO_DEF_MAX_PULSE_US;
			servoData[15].pos = pos;
			servoInitPwmTimer1(&TCE1, &PORTE, PIN5_bm);
			break;
	}
	
	servoSetAngle(servoNo, pos);
}

void servoSetAngle(uint8_t servoNo, uint8_t angle)
{
	servoData[servoNo].pos = angle;
	
	uint16_t us = mapValue(angle, 0, 180, servoData[servoNo].minPulse, servoData[servoNo].maxPulse);
	
	if (servoData[servoNo].timer1 == NULL)
		servoSetWidthTimer0(servoData[servoNo].timer0, servoData[servoNo].pin, us);
	else if (servoData[servoNo].timer0 == NULL)
		servoSetWidthTimer1(servoData[servoNo].timer1, servoData[servoNo].pin, us);
}

void servoSetMinPulse(uint8_t servoNo, uint16_t minPulse_us)
{
	servoData[servoNo].minPulse = minPulse_us;
	//update pos:
	servoSetAngle(servoNo, servoData[servoNo].pos);
}

void servoSetMaxPulse(uint8_t servoNo, uint16_t maxPulse_us)
{
	servoData[servoNo].maxPulse = maxPulse_us;
	//update pos:
	servoSetAngle(servoNo, servoData[servoNo].pos);
}

uint16_t servoGetPeriod(uint8_t servoNo)
{
	if (servoData[servoNo].timer1 == NULL)
		return ticksToUs(servoData[servoNo].timer0->PER, SERVO_PRESC);
	else
		return ticksToUs(servoData[servoNo].timer1->PER, SERVO_PRESC);
}

void servoSetPeriod(uint8_t servoNo, uint16_t period_us)
{
	if (servoData[servoNo].timer1 == NULL)
		servoSetPeriodTimer0(servoData[servoNo].timer0, period_us);
	else if (servoData[servoNo].timer0 == NULL)
		servoSetPeriodTimer1(servoData[servoNo].timer1, period_us);
}