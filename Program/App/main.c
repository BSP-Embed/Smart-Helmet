#include "main.h"

extern int8u lcdptr;
struct App Flags;

int main(void) {
	init();
	while (TRUE) {
		if (Flags.Check) {
			ChkHelm();
			if (Flags.Moving)
				ChkAlco();
			Flags.Check = FALSE;
		}
		if (Flags.Vibr) 
			Accident();
		if (Flags.sw ) 
			IgnSw();
		sleep();	
	}
	return 0;
}
static void init(void) {
	buzinit();
	ledinit();
	beep(2,100);
	motorinit();
	lcdinit();
	uartinit();
	EXTINTinit();
	GPSInit();
	GSMEn();
	GSMinit();
	tmr1init();
	RFRxInit();
	disptitl();
	sei();
	sleep();
}
static void Accident(void) {
	Flags.Vibr = FALSE;
	lcdclrr(1);
	lcdws("Accident Occur'd");
	beep(1,250);
	dlyms(1000);
	SendLinkLoc(RPhNum,"Your Vehicle Got Accident at ");
	lcdclr();
	lcdws("Accident Occur'd");
	Reset();
}
static void IgnSw(void) {
	if (Flags.HelmetOn){
		beep(1,100);
		if (!Flags.state) {
			Flags.state = TRUE;
			moton();
			lcdclrr(1);
			lcdws(" Vehicle Moving");
			Flags.Moving = TRUE;
		} else {
			Flags.state = FALSE;
			motoff();
			lcdclrr(1);
			lcdws(" Vehicle Stopped");
			Flags.Moving = FALSE;
		}
	}
	Flags.sw = FALSE;
}
static void ChkHelm(void) {
	if (RFPPIN & _BV(RFVDPIN)) {
		if (!Flags.HelmetOn) {
			Flags.HelmetOn = TRUE;
			lcdclrr(1);
			lcdws(" Helmet Weared");
			beep(1,150);
			GICR |= _BV(INT1);			/* ENABLE EXTERNAL INTERRUPT */
		}
	} else {
		if (Flags.HelmetOn) {
			Flags.HelmetOn = FALSE;
			Flags.state = FALSE;
			Flags.Moving = FALSE;
			lcdclrr(1);
			lcdws(" Helmet Removed");
			GICR &=  ~_BV(INT1);		/* Disable Switch */
			motoff();
			beep(1,150);
			dlyms(1000);
			lcdclrr(1);
			lcdws(" Vehicle Stopped");
			dlyms(1000);
		}
	}
}
static void ChkAlco(void) {
	if ((RFPPIN & _BV(RFDATA3)) == 0) 	{
		lcdclr();
		lcdws("Alcohol Consumed");
		motoff();
		GICR &=  ~_BV(INT1);		/* Disable Switch */
		beep(1,250);
		Reset();
	} 
}
static void Reset(void) {
	lcdclrr(1);
	lcdws(" Reset to START");
	beep(2,500);
	cli();
	ledon();
	sleep();
	for(;;);
}
static void EXTINTinit(void) {
	INTDDR 	&= ~(_BV(INT0_PIN) | _BV(INT1_PIN));
	INTPORT |= (_BV(INT0_PIN) | _BV(INT1_PIN));

	GICR |= _BV(INT0) | _BV(INT1);			//ENABLE EXTERNAL INTERRUPT
	MCUCR |= _BV(ISC01) | _BV(ISC11);		//FALLING EDGE INTERRUPT

}
static void disptitl(void) {
	lcdclr();
	lcdws("  SMART HELMET");
}
static void Flagsinit(void) {
	Flags.HelmetOn = FALSE;
	Flags.Check = FALSE;
	Flags.Moving = FALSE;
	Flags.state = FALSE;
	Flags.sw = FALSE;
	Flags.Vibr = FALSE;
}		
ISR(INT0_vect) { 
	Flags.Vibr = TRUE;
	GICR |= _BV(INT0);
}
ISR(INT1_vect) {
	Flags.sw = TRUE;
	GICR |= _BV(INT1);
}
static void tmr1init(void) {
	TCNT1H   = 225;					/* overflows at every 250msec */
	TCNT1L   = 123;
	TIMSK   |= _BV(TOIE1);			/* ENABLE OVERFLOW INTERRUPT */
	TCCR1A   = 0x00;
	TCCR1B  |= _BV(CS12);			 /* PRESCALAR BY 256 */
}
/* overflows at every 250msec */
ISR(TIMER1_OVF_vect) {
	static int8u i, j, k;
	TCNT1H   = 225;					/* overflows at every 250msec */
	TCNT1L   = 123;
	if (!Flags.Check && ++j >= 2) {
		Flags.Check = TRUE;
		j = 0;
	}
	if (++i >= 20)	i = 0;
	switch(i) {
		case 0: case 2: ledon(); break;
		case 1: case 3: ledoff(); break;
	}
}