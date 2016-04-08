#include "uart.h"

//Private stuff:
static uint8_t linesReceived;
static CircBuff receiveBuffer;

ISR(UART_RX_VECT)
{
	uint8_t data = UART.DATA;

	if (!circBuffIsFull(&receiveBuffer))
	{
		if (data == '\n')
			++linesReceived;
		circBuffAdd(&receiveBuffer, data);
	}
}


static bool uartSetBaudRate(USART_t * const usart, uint32_t baud, uint32_t cpu_hz)
{
	int8_t exp;
	uint32_t div;
	uint32_t limit;
	uint32_t ratio;
	uint32_t min_rate;
	uint32_t max_rate;

	/*
	 * Check if the hardware supports the given baud rate
	 */
	/* 8 = (2^0) * 8 * (2^0) = (2^BSCALE_MIN) * 8 * (BSEL_MIN) */
	max_rate = cpu_hz / 8;
	/* 4194304 = (2^7) * 8 * (2^12) = (2^BSCALE_MAX) * 8 * (BSEL_MAX+1) */
	min_rate = cpu_hz / 4194304;

	if (!((usart)->CTRLB & USART_CLK2X_bm)) {
		max_rate /= 2;
		min_rate /= 2;
	}

	if ((baud > max_rate) || (baud < min_rate)) {
		return false;
	}

	/* Check if double speed is enabled. */
	if (!((usart)->CTRLB & USART_CLK2X_bm)) {
		baud *= 2;
	}

	/* Find the lowest possible exponent. */
	limit = 0xfffU >> 4;
	ratio = cpu_hz / baud;

	for (exp = -7; exp < 7; exp++) {
		if (ratio < limit) {
			break;
		}

		limit <<= 1;

		if (exp < -3) {
			limit |= 1;
		}
	}

	/*
	 * Depending on the value of exp, scale either the input frequency or
	 * the target baud rate. By always scaling upwards, we never introduce
	 * any additional inaccuracy.
	 *
	 * We are including the final divide-by-8 (aka. right-shift-by-3) in
	 * this operation as it ensures that we never exceeed 2**32 at any
	 * point.
	 *
	 * The formula for calculating BSEL is slightly different when exp is
	 * negative than it is when exp is positive.
	 */
	if (exp < 0) {
		/* We are supposed to subtract 1, then apply BSCALE. We want to
		 * apply BSCALE first, so we need to turn everything inside the
		 * parenthesis into a single fractional expression.
		 */
		cpu_hz -= 8 * baud;

		/* If we end up with a left-shift after taking the final
		 * divide-by-8 into account, do the shift before the divide.
		 * Otherwise, left-shift the denominator instead (effectively
		 * resulting in an overall right shift.)
		 */
		if (exp <= -3) {
			div = ((cpu_hz << (-exp - 3)) + baud / 2) / baud;
		} else {
			baud <<= exp + 3;
			div = (cpu_hz + baud / 2) / baud;
		}
	} else {
		/* We will always do a right shift in this case, but we need to
		 * shift three extra positions because of the divide-by-8.
		 */
		baud <<= exp + 3;
		div = (cpu_hz + baud / 2) / baud - 1;
	}

	(usart)->BAUDCTRLB = (uint8_t)(((div >> 8) & 0X0F) | (exp << 4));
	(usart)->BAUDCTRLA = (uint8_t)div;

	return true;
}

bool uartInit(uint32_t baudRate, uint8_t stopBits, uint8_t parity)
{
	if (!circBuffInit(&receiveBuffer, UART_BUFFER_SIZE))
		return false;
	
    //Zero all registers:
    UART.CTRLA = 0;
    UART.CTRLB = 0;
    UART.CTRLC = 0;

    //Set baud rate using ASF function
    if (!uartSetBaudRate(&UART, baudRate, F_CPU))
        return false;

    //Set stop bits:
	if (stopBits == 2)
        UART.CTRLC |= USART_SBMODE_bm;

	//Set parity:
	switch (parity)
	{
		case 1: //Odd parity
			UART.CTRLC |= USART_PMODE_ODD_gc;
			break;
		case 2: //Even parity
			UART.CTRLC |= USART_PMODE_EVEN_gc;
			break;
	}

	//Set interrupt (low level)
    UART.CTRLA |= USART_RXCINTLVL_LO_gc;
    //PMIC.CTRL |= PMIC_LOLVLEN_bm;

	//Set TX pin as datasheet mentions
    UART_PORT.OUTSET |= PIN3_bm;
    UART_PORT.DIRSET |= PIN3_bm;
	UART_PORT.OUTCLR |= PIN2_bm;

    //Set 8 bit frame format
    UART.CTRLC |= USART_CHSIZE_8BIT_gc;

    //Enable transmitter and receiver
    UART.CTRLB |= USART_TXEN_bm | USART_RXEN_bm;


	//Open output stream
	static FILE uartStream = FDEV_SETUP_STREAM(uartPutChar, NULL, _FDEV_SETUP_WRITE);
	stdout = &uartStream;

	return true;
}

int uartPutChar(char ch, FILE *stream)
{
	while (!(UART.STATUS & USART_DREIF_bm));
    UART.DATA = ch;

	return 0;
}

char uartGetChar(void)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (!circBuffIsEmpty(&receiveBuffer))
		{
			char tempRead = circBuffRead(&receiveBuffer);
			if (tempRead == '\n')
				--linesReceived;
			return tempRead;
		}
	}
	return 0;
}

uint8_t uartGetLine(char *strDest, uint8_t length)
{
	if (linesReceived == 0)
		return -1;

	for (uint8_t i = 0; i < length - 1; ++i)
	{
		char tempRead = uartGetChar();

		if (tempRead == '\n')
		{
			strDest[i] = '\0';
			return 0;
		}

		strDest[i] = tempRead;
	}
	strDest[length - 1] = '\0';

	if (circBuffPeek(&receiveBuffer) == '\n')
	{
		uartGetChar();
		return 0;
	}
	--linesReceived;
	
	return 1;
}

uint8_t uartLinesReceived(void)
{
	return linesReceived;
}

bool uartBufferIsEmpty(void)
{
	return circBuffIsEmpty(&receiveBuffer);
}

bool uartBufferIsFull(void)
{
	return circBuffIsFull(&receiveBuffer);
}

void uartFlush(void)
{
	while (!uartBufferIsEmpty())
		circBuffRead(&receiveBuffer);

	linesReceived = 0;
}
