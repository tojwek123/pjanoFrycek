#include "commandExecution.h"

static bool ShowLog = true;

uint8_t executeCmd(char *str)
{		
	uint8_t cmdNum;
	
	//get num of command:
	if (sscanf(str, "%hhu", &cmdNum) != 1)
		return BAD_FORMAT;
	
	//skip first number (no '\0' is guarantee due to previous scanf):
	while (isspace(*str)) ++str;
	while (isdigit(*str)) ++str;	
	
	switch (cmdNum)
	{
		case SERVO_SET_ANGLE:
			return execServoSetAngle(str);	
			break;
		case SERVO_SET_ANGLE_ALL:
			return execServoSetAngleAll(str);
			break;
		case SERVO_SET_MIN_PULSE:
			return execServoSetMinPulse(str);
			break;
		case SERVO_SET_MAX_PULSE:
			return execServoSetMaxPulse(str);
			break;
		case SERVO_SET_PERIOD:
			return execServoSetPeriod(str);
			break;
		case SERVO_GET_POS:
			return execServoGetPos(str);
			break;
		case SERVO_GET_POS_ALL:
			return execServoGetPosAll(str);
			break;
		case SERVO_GET_INFO:
			return execServoGetInfo(str);
			break;
		case SERVO_GET_INFO_ALL:
			return execServoGetInfoAll(str);
			break;
		case SHOW_LOG:
			return execShowLog(str);
			break;
		default:
			return BAD_CMD;
	}
}

uint8_t execServoSetAngle(char *str)
{
	uint8_t servoNo, pos;
	
	if (sscanf(str, "%hhu %hhu", &servoNo, &pos) != 2)
		return BAD_ARG;
	
	servoSetAngle(servoNo, pos);
	
	if (ShowLog)
		uartWrite("Servo %d: %d deg\r\n", servoNo, pos);
	
	return CMD_GOOD;
}
uint8_t execServoSetAngleAll(char *str)
{
	uint8_t pos[SERVO_AMNT];
	
	for (uint8_t i = 0; i < SERVO_AMNT; ++i)
	{
		if (sscanf(str, "%hhu", &pos[i]) != 1)
			return BAD_ARG;
		
		//move pointer after all digits except last one
		if (i < SERVO_AMNT - 1)
		{
			while (isspace(*str)) ++str;
			while (isdigit(*str)) ++str;
		}
	}
	
	for (uint8_t i = 0; i < SERVO_AMNT; ++i)
	{
		servoSetAngle(i, pos[i]);
		
		if (ShowLog)
			uartWrite("Servo %d: %d deg\r\n", i, pos[i]);
	}
	
	return CMD_GOOD;
}
uint8_t execServoSetMinPulse(char *str)
{
	uint8_t servoNo;
	uint16_t minPulse;
	
	if (sscanf(str, "%hhu %u", &servoNo, &minPulse) != 2)
		return BAD_ARG;
	
	servoSetMinPulse(servoNo, minPulse);
	
	if (ShowLog)
		uartWrite("Servo %d minPulse: %u us\r\n", servoNo, minPulse);
	
	return CMD_GOOD;
}
uint8_t execServoSetMaxPulse(char *str)
{
	uint8_t servoNo;
	uint16_t maxPulse;
	
	if (sscanf(str, "%hhu %u", &servoNo, &maxPulse) != 2)
		return BAD_ARG;
	
	servoSetMaxPulse(servoNo, maxPulse);
	
	if (ShowLog)
		uartWrite("Servo %d maxPulse: %u us\r\n", servoNo, maxPulse);
		
	return CMD_GOOD;
}
uint8_t execServoSetPeriod(char *str)
{
	uint8_t servoNo;
	uint16_t period;
	
	if (sscanf(str, "%hhu %u", &servoNo, &period) != 2)
		return BAD_ARG;
	
	servoSetPeriod(servoNo, period);
	
	if (ShowLog)
		uartWrite("Servo %d period: %u us\r\n", servoNo, servoGetPeriod(servoNo));
	
	return CMD_GOOD;
}
uint8_t execServoGetPos(char *str)
{
	uint8_t servoNo, format;
	
	if (sscanf(str, "%hhu %hhu", &servoNo, &format) != 2)
		return BAD_ARG;
	
	if (format == FORMAT_NUM)
		uartWrite("%d\r\n", servoGetPos(servoNo));
	else if (format == FORMAT_FULL)
		uartWrite("Servo %d: %d deg\r\n", servoNo, servoGetPos(servoNo));
	else
		return BAD_ARG;
	
	return CMD_GOOD;
}
uint8_t execServoGetPosAll(char *str)
{
	uint8_t format;
	
	if (sscanf(str, "%hhu", &format) != 1)
		return BAD_ARG;
	
	for (uint8_t i = 0; i < SERVO_AMNT; ++i)
	{
		if (format == FORMAT_NUM)
			uartWrite("%d\r\n", servoGetPos(i));
		else if (format == FORMAT_FULL)
			uartWrite("Servo %d: %d deg\r\n", i, servoGetPos(i));
		else
			return BAD_ARG;
	}
	
	return CMD_GOOD;
}
uint8_t execServoGetInfo(char *str)
{
	uint8_t servoNo, format;
	
	if (sscanf(str, "%hhu %hhu", &servoNo, &format) != 2)
		return BAD_ARG;
	
	if (format == FORMAT_NUM)
	{
		uartWrite("%d %d %d %d\r\n", servoGetPos(servoNo), servoGetMinPulse(servoNo), servoGetMaxPulse(servoNo), servoGetPeriod(servoNo));
	}
	else if (format == FORMAT_FULL)
	{
		uartWrite("Servo %d\r\n", servoNo);
		uartWrite("Pos: %d deg\r\n", servoGetPos(servoNo));
		uartWrite("MinPulse: %d us\r\n", servoGetMinPulse(servoNo));
		uartWrite("MaxPulse: %d us\r\n", servoGetMaxPulse(servoNo));
		uartWrite("Period: %d us\r\n", servoGetPeriod(servoNo));
	}
	else
		return BAD_ARG;
		
	return CMD_GOOD;
}
uint8_t execServoGetInfoAll(char *str)
{
	uint8_t format;
	
	if (sscanf(str, "%hhu", &format) != 1)
		return BAD_ARG;
	
	for (uint8_t i = 0; i < SERVO_AMNT; ++i)
	{
		if (format == FORMAT_NUM)
		{
			uartWrite("%d %d %d %d\r\n", servoGetPos(i), servoGetMinPulse(i), servoGetMaxPulse(i), servoGetPeriod(i));
		}
		else if (format == FORMAT_FULL)
		{
			uartWrite("Servo %d\r\n", i);
			uartWrite("Pos: %d deg\r\n", servoGetPos(i));
			uartWrite("MinPulse: %d us\r\n", servoGetMinPulse(i));
			uartWrite("MaxPulse: %d us\r\n", servoGetMaxPulse(i));
			uartWrite("Period: %d us\r\n", servoGetPeriod(i));
		}
		else
			return BAD_ARG;
	}
	return CMD_GOOD;
}
uint8_t execShowLog(char *str)
{
	uint8_t show;
	
	if (sscanf(str, "%hhu", &show) != 1)
		return BAD_ARG;
	
	if (ShowLog)
	{
		if (show)
		uartWrite("Show log: true\r\n");
		else
		uartWrite("Show log: false\r\n");
	}
	else
		if (show)
			uartWrite("Show log: true\r\n");
	
	ShowLog = show;
	
	return CMD_GOOD;
}