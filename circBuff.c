#include "circBuff.h"

bool circBuffInit(CircBuff *cb, uint16_t size)
{
	cb->buffMem = (circBuffType*)malloc(size * sizeof(circBuffType));
	
	if (cb->buffMem == NULL)
		return false;
	
	cb->beginning = 0; 
	cb->amntOfElements = 0;
	cb->size = size;
	
	return true;
}

bool circBuffAdd(CircBuff *cb, circBuffType element)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (circBuffIsFull(cb))
		return false;

		uint8_t end = (cb->beginning + cb->amntOfElements) % cb->size;
		cb->buffMem[end] = element;
		++cb->amntOfElements;
	}

	return true;
}

uint8_t circBuffRead(CircBuff *cb)
{
	circBuffType element;
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (circBuffIsEmpty(cb))
		return 0;

		element = cb->buffMem[cb->beginning];
		cb->beginning = (cb->beginning + 1) % cb->size;
		--cb->amntOfElements;
	}

	return element;
}

circBuffType circBuffPeek(CircBuff *cb)
{
	circBuffType element = cb->buffMem[cb->beginning];
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (circBuffIsEmpty(cb))
		return 0;
	}
	
	return element;
}