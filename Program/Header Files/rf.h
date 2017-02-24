#ifndef RF_H
#define RF_H

#include "includes.h"

//DEFINE MACROS
#define EnRF()		do {							\
						RFPORT &= ~_BV(RFEN_PIN);	\
						dlyms(100);					\
						RFPORT |= _BV(RFEN_PIN);	\
						dlyms(200);					\
					} while (0);

/**** FUNCTION PROTOTYPES    ******/
void rfinit		(void);
void RFRxInit	(void);
void trans		(const char *str);

#endif