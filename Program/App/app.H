#ifndef _APP_H
#define _APP_H

#include "types.h"

/* Main settings */

/********** GPS & GSM MUX CONFIGURATION ***********/
#define GSM_GPS_DDR				DDRD
#define GSM_GPS_PORT			PORTD
#define GSM_GPS_PIN				PD7

/******** GPS & GSM MUX CONFIGURATION ENDS *******/

/* LCD CONFIGURATION */
#define LCD_DDR           	   		DDRC 
#define LCD_DATA_PORT          		PORTC
#define LCD_ENABLE_PIN        		PC3 
#define LCD_REGISTER_SELECT_PIN     PC2
#define DISPLAY_INIT				1
#define LCD_NSCRL					0
#define FLOAT_T0_STRING				1
#define DECIMAL_PRECISION			10

/******** LCD CONFIGURATION ENDS ****************/

/* BUZZER: CONFIGURATION */
#define	BUZ_DDR						DDRC
#define	BUZ_PORT					PORTC
#define	BUZ_PIN						PC1
#define OFF_TIME					100
/******** BUZZER CONFIGURATION ENDS ****************/

/* LED: CONFIGURATION */

#define	LED_DDR			DDRC
#define	LED_PORT		PORTC
#define	LED_PIN			PC0

#define OFF_TIME		100
/******** LED CONFIGURATION ENDS ****************/

/* GSM: CONFIGURATION */
#define RPhNum	 "PH_NUMBER"


#define MSG_START		""
#define MSG_END			". Automated SMS By:SH"

#define GSMEn()				do {										\
									GSM_GPS_PORT &= ~_BV(GSM_GPS_PIN); 	\
									dlyms(500);							\
								} while(0)

#define GPSEn()				do {									\
								GSM_GPS_PORT |= _BV(GSM_GPS_PIN);	\
								dlyms(500);							\
							} while(0)

/******** ADC CONFIGURATION ENDS ****************/
#define REF_VOL_256

/******** EEPROM CONFIGURATION ****************/
#define EEPROM_DISPLAY		0

/******** MOTOR CONFIGURATION *****************/
#define MOT_DDR			DDRA
#define MOT_PORT		PORTA
#define MOT1_AN			PA3
#define MOT1_CA			PA4
#define MOT2_AN			PA5
#define MOT2_CA			PA6

/****** ALCOHOL SENSOR CONFIGURATION *******/
#define ALCO_SENS_DDR			DDRB
#define ALCO_SENS_PORT			PORTB
#define ALCO_SENS_PPIN			PINB
#define ALCO_SENS_PIN			PB7
/***** ALCOHOL CONFIGURATION ENDS   *******/

/****** RF CONFIGURATION ********/
#define RFDDR			DDRB
#define RFPORT			PORTB
#define RFPPIN			PINB
#define RFVDPIN			PB0
#define RFDATA3			PB1
#define RFEN_PIN		PB2
/****** RF CONFIGURATION ENDS  *****/

/* DEFINE Flag Structure Definition */
struct  App{
	volatile int8u sw:1;
	volatile int8u Check:1;
	volatile int8u HelmetOn:1;
	volatile int8u HelmetOff:1;
	volatile int8u state:1;
	volatile int8u Vibr:1;
	volatile int8u Moving:1;
	volatile int8u Msg:1;
};
#endif
