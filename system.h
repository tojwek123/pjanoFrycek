#ifndef system_h
#define system_h

#include <avr/io.h> 
#include <stdbool.h>
#include <util/delay.h>

#define OSC_FAIL_TIME 255

#define INT_LOW PMIC_LOLVLEN_bm
#define INT_MED PMIC_MEDLVLEN_bm
#define INT_HI	PMIC_HILVLEN_bm

bool systemSetClk32Mhz();
static inline void systemInterruptEnable(uint8_t INT_bm) {PMIC.CTRL |= INT_bm;}
	
#endif