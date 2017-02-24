#ifndef ALCOHOL_H
#define ALCOHOL_H

#include "includes.h"

#define alcodet()			((ALSENS_PPIN & _BV(ALSENS_PIN)) == 0)


void	AlcoSensInit	(void);

#endif