/* gps.c: device driver for GPS receiver interface */

#include"gps.h"

void GPSInit(void) {
	GSM_GPS_DDR |= _BV(GSM_GPS_PIN);
	GSM_GPS_PORT &= ~_BV(GSM_GPS_PIN);
}
void GPSgetloc(int8u *Lat, int8u *Lon)
{
	int8u i;
ReadAgain:
	while(getchar() != '$');
	if(getchar() != 'G')
		goto ReadAgain;
	if(getchar() != 'P')
 		goto ReadAgain;
	if(getchar() != 'G')
		goto ReadAgain;
	if(getchar() != 'G')
		goto ReadAgain;
	if(getchar() != 'A')
		goto ReadAgain;
	while(getchar() != ',');
	while(getchar() != ',');
	for(i = 0; i < 9; i++)
		*Lat++ = getchar();
	while(getchar() != 'N');
	while(getchar() != ',');
	for(i = 0; i < 10; i++)
		*Lon++ = getchar();
}
