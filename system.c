#include "system.h"

bool systemSetClk32Mhz()
{
	OSC.CTRL = OSC_RC32MEN_bm;
	int oscCounter = 0;
	while (!(OSC.STATUS & OSC_RC32MRDY_bm))
	{
		_delay_ms(1);
		++oscCounter;
		
		if (oscCounter > OSC_FAIL_TIME)
		return false;
	}
	CCP = CCP_IOREG_gc;
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;
	
	return true;
}