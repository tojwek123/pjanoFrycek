#ifndef COMMANDEXECUTION_H_
#define COMMANDEXECUTION_H_

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "registerDefines.h"
#include "servo.h"
#include "uart.h"

//FORMAT
#define FORMAT_NUM	0
#define FORMAT_FULL 1

//ERROR_CODES
#define CMD_GOOD	0
#define BAD_CMD		1
#define BAD_ARG		2
#define BAD_FORMAT	3

uint8_t executeCmd(char *str);

uint8_t execServoSetAngle(char *str);
uint8_t execServoSetAngleAll(char *str);
uint8_t execServoSetMinPulse(char *str);
uint8_t execServoSetMaxPulse(char *str);
uint8_t execServoSetPeriod(char *str);
uint8_t execServoGetPos(char *str);
uint8_t execServoGetPosAll(char *str);
uint8_t execServoGetInfo(char *str);
uint8_t execServoGetInfoAll(char *str);
uint8_t execShowLog(char *str);

#endif