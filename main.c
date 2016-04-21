#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>

#include "servo.h"
#include "uart.h"
#include "system.h"
#include "commandExecution.h"
#include "stepper.h"

#define CMD_LENGTH 50

void badInitAlarm();

int main(void)
{
	PORTA.DIRSET = PIN0_bm;
	PORTA.OUTSET = PIN0_bm;
	
	if (!systemSetClk32Mhz())
		badInitAlarm();
    if (!uartInit(19200, 1, 1))
		badInitAlarm();
	
	stepperInit(800, 255, 0, 255);

	//attach all servos:
	/*
	for (uint8_t i = 0; i < SERVO_AMNT; ++i)
		servoAttach(i, 45);*/
		
	systemInterruptEnable(INT_LOW);
	sei();
	
	char str[CMD_LENGTH];
	
    while (1)
    {		
		if (uartLinesReceived() > 0)
		{
			uartGetLine(str, CMD_LENGTH);

			switch (executeCmd(str))
			{
				case BAD_FORMAT:
					uartWrite("Err - cmd is NaN\r\n");
					break;
				case BAD_ARG:
					uartWrite("Err - not enough args or NaN\r\n");
					break;
				case BAD_CMD:
					uartWrite("Err - invalid cmd\r\b");
					break;
			}
		}
    }
}

void badInitAlarm()
{
	PORTA.DIRSET = PIN0_bm;
	PORTA.OUTCLR = PIN0_bm;
	
	while (1)
	{
		PORTA.OUTTGL = PIN0_bm;
		_delay_ms(100);
	}
}