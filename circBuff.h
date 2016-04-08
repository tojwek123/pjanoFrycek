#ifndef CircBuff_h
#define CircBuff_h

#include <stdint.h>
#include <stdbool.h>
#include <util/atomic.h>
#include <stdlib.h>

typedef uint8_t circBuffType;

typedef struct
{
	circBuffType *buffMem;
	uint16_t beginning;
	uint16_t amntOfElements;
	uint16_t size; 
} CircBuff;

bool circBuffInit(CircBuff *cb, uint16_t size);

static inline bool circBuffIsFull(CircBuff *cb) {return cb->amntOfElements == cb->size;}
static inline bool circBuffIsEmpty(CircBuff *cb) {return cb->amntOfElements == 0;}
	
bool circBuffAdd(CircBuff *cb, circBuffType element);

circBuffType circBuffRead(CircBuff *cb);
circBuffType circBuffPeek(CircBuff *cb);

#endif