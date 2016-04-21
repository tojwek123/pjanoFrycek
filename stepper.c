#include "stepper.h"

//Array is used to provide easy changes between types of steering
static uint8_t StepperPinout[] = {0b0001, 0b0100, 0b0010, 0b1000};

ISR(STEPPER_OVF_vect)
{
	if (stepperData.requiredPos > stepperData.currentPos)
		STEPPER_OUTPUT_PORT.OUT = StepperPinout[++stepperData.currentPos % 4];
	else if (stepperData.requiredPos < stepperData.currentPos)
		STEPPER_OUTPUT_PORT.OUT = StepperPinout[--stepperData.currentPos % 4];
	else
		STEPPER_PWM_TIM.CCABUF = stepperData.holdPWM;
}

void stepperInit(uint16_t freq, uint16_t steps, uint8_t holdPWM, uint8_t movePWM)
{
	stepperData.steps = steps;
	stepperData.holdPWM = holdPWM;
	stepperData.movePWM = movePWM;
	stepperData.requiredPos = 0;
	stepperData.currentPos = 0;
	
	//init timer:
	stepperSetFreq(freq);
	STEPPER_OVF_TIM.INTCTRLA = TC_OVFINTLVL_LO_gc;
	STEPPER_OVF_TIM.CTRLA = TC_CLKSEL_DIV256_gc;
	
	//PWM pins:
	STEPPER_PWM_PORT.DIRSET |= STEPPER_PWM_PIN;
	
	//timer for PWM
	STEPPER_PWM_TIM.CTRLB = TC1_CCAEN_bm | TC_WGMODE_SINGLESLOPE_gc;
	STEPPER_PWM_TIM.CTRLA = TC_CLKSEL_DIV64_gc;
	STEPPER_PWM_TIM.PER = 255;
	STEPPER_PWM_TIM.CCA = stepperData.holdPWM;
	
	//outputs:
	STEPPER_OUTPUT_PORT.DIRSET |= PIN0_bm | PIN1_bm |  PIN2_bm | PIN3_bm;
	STEPPER_OUTPUT_PORT.OUT |= StepperPinout[0];
}

void stepperSetFreq(uint16_t Hz) 
{
	if (Hz < STEPPER_FREQ_MIN)
		Hz = STEPPER_FREQ_MIN;
	else if (Hz > STEPPER_FREQ_MAX)
		Hz = STEPPER_FREQ_MAX;
		
	stepperData.freq = Hz; 
	STEPPER_OVF_TIM.PERBUF = F_CPU / 256 / Hz;
}

void stepperSetPos(uint16_t pos)
{
	if (pos < stepperData.steps + 1)
	{
		STEPPER_PWM_TIM.CCABUF = stepperData.movePWM;
		
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			stepperData.requiredPos = pos;
		}
	}
}

uint16_t stepperGetPos()
{
	uint16_t pos;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {pos = stepperData.currentPos; }
	return pos;
}

void stepperSetHoldPWM(uint8_t holdPWM)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		stepperData.holdPWM = holdPWM;
	}
}
void stepperSetMovePWM(uint8_t movePWM)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		stepperData.movePWM = movePWM;
	}
}