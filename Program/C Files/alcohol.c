#include "alcohol.h"

void AlcoSensInit(void) {
	ALSENS_DDR &= ~_BV(ALSENS_PIN);
	ALSENS_PORT |= _BV(ALSENS_PIN);
	
	lcdclrr(1);
	lcdws("Sensor Init:");
	while ((ALSENS_PPIN & _BV(ALSENS_PIN)) == 0);
	lcdws("Ok");
	dlyms(DISP_DLY);
	
}