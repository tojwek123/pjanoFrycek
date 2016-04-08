#ifndef uart_h
#define uart_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "circBuff.h"

#define UART            USARTD0
#define UART_RX_VECT    USARTD0_RXC_vect
#define UART_PORT       PORTD

#define UART_BUFFER_SIZE 50

#define uartWrite 	printf
#define uartWrite_P printf_P

bool uartInit(uint32_t baudRate, uint8_t stopBits, uint8_t parity);

int uartPutChar(char ch, FILE *stream);
char uartGetChar(void);

uint8_t uartGetLine(char *strDest, uint8_t length);
uint8_t uartLinesReceived(void);

bool uartBufferIsEmpty(void);
bool uartBufferIsFull(void);

void uartFlush(void);
#endif
