#ifndef stepper_h
#define stepper_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdbool.h>

#define STEPPER_OVF_TIM		TCF0	//for OVF interrupt
#define STEPPER_PWM_TIM		TCD1	//for PWM
#define STEPPER_PWM_PORT	PORTD	//PIN 4 and PIN 5 are used
#define STEPPER_PWM_PIN		PIN4_bm
#define STEPPER_OVF_vect	TCF0_OVF_vect

#define STEPPER_OUTPUT_PORT PORTC	//whole port is required

#define STEPPER_FREQ_MAX 1000
#define STEPPER_FREQ_MIN 100

struct
{
	uint16_t freq;
	uint16_t steps;
	uint8_t holdPWM;
	uint8_t movePWM;
	uint16_t requiredPos;
	volatile uint16_t currentPos;
} stepperData;

void stepperInit(uint16_t freq, uint16_t steps, uint8_t holdPWM, uint8_t movePWM);

void stepperSetHoldPWM(uint8_t holdPWM);
void stepperSetMovePWM(uint8_t movePWM);
void stepperSetPos(uint16_t pos);
void stepperSetFreq(uint16_t Hz);

static inline bool stepperReady() {return stepperData.currentPos == stepperData.requiredPos;}

uint16_t stepperGetPos();
static inline uint16_t stepperSteps() {return stepperData.steps;}

static inline void stepperInc() {stepperSetPos(stepperData.currentPos + 1);}
static inline void stepperDec() {stepperSetPos(stepperData.currentPos - 1);}

#endif