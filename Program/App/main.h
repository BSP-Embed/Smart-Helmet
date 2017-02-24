#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define INTDDR				DDRD
#define INTPORT				PORTD
#define INT0_PIN			PD2
#define INT1_PIN			PD3

#define moton()				MotClk()
#define motoff()			MotStop()

							
//FUNCTION PROTOTYPES
static void		init		(void);
static void 	disptitl 	(void);
static void 	tmr1init	(void);
static void 	EXTINTinit	(void);
static void		Accident	(void);
static void		IgnSw		(void);
static void		ChkHelm		(void);
static void		ChkAlco		(void); 
static void		Reset		(void);
#endif

