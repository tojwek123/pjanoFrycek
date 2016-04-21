//Port usage:
//
//TCC0 (0:3), TCC1(4:5) = 6
//TCE0 (0:3), TCE1(4:5) = 6
//TCD0 (0:3)			= 4
//..................... = 16

#ifndef servo_h
#define servo_h

#include <stdlib.h>

#include "servo_base.h"
#include "utils.h"

#define C0 0
#define C1 1
#define C2 2
#define C3 3
#define C4 4
#define C5 5

#define D0 6
#define D1 7
#define D2 8
#define D3 9

#define E0 10
#define E1 11
#define E2 12
#define E3 13
#define E4 14
#define E5 15

#define SERVO_AMNT 16

typedef struct
{
	TC0_t *timer0;
	TC1_t *timer1;
	PORT_t *port;
	uint8_t pin;
	uint16_t minPulse;
	uint16_t maxPulse;
	uint8_t pos;
} ServoInfo;

ServoInfo servoData[SERVO_AMNT];

void servoAttach(uint8_t servoNo, uint8_t angle);
void servoSetAngle(uint8_t servoNo, uint8_t angle);
void servoSetMinPulse(uint8_t servoNo, uint16_t minPulse_us);
void servoSetMaxPulse(uint8_t servoNo, uint16_t maxPulse_us);
void servoSetPeriod(uint8_t servoNo, uint16_t period_us);

static inline uint16_t servoGetMinPulse(uint8_t servoNo) {return servoData[servoNo].minPulse;}
static inline uint16_t servoGetMaxPulse(uint8_t servoNo) {return servoData[servoNo].maxPulse;}
uint16_t servoGetPeriod(uint8_t servoNo);
static inline uint8_t servoGetPos(uint8_t servoNo) {return servoData[servoNo].pos;}

#endif
