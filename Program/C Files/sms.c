#include "sms.h"

extern int8u OTP[5];
extern struct App Flags;
char PhNum[12], sbuf[10];

void SendOTP(const char *PNum,const char *GSMMsg) {
	int8u gsmmsg[150];
	gsmmsg[0] = '\0';
	genOTP(OTP);
	strcat(gsmmsg,GSMMsg);
	strcat(gsmmsg,OTP);
	GSMEn();
	GSMsndmsg(PNum, gsmmsg);
}

void sendloc(const char *PhNum, const char *GSMMsg) {
	int8u i;
	int8u lat[11];
	int8u lon[11];
	int8u gsmmsg[150];

	gsmmsg[0] = '\0';

	for (i = 0; i < 10; i++)
		lat[i] = lon[i] = '0';

	lat[10] = lon[10] = '\0';

	GPSEn();
	GPSgetloc(lat,lon);

	strcat(gsmmsg,GSMMsg);
	strcat(gsmmsg," LAT:");
	strcat(gsmmsg,lat);
	strcat(gsmmsg," & LON: ");
	strcat(gsmmsg,lon);

	GSMEn();
	GSMsndmsg(PhNum, gsmmsg);
}

void SendLinkLoc(const char *PhNum, const char *GSMMsg) {
	int8u i;
	int8u lat[11];
	int8u lon[11];
	int8u gsmmsg[150];
	int8u latl[3];
	int8u latu[10];	
	int8u lonl[4];
	int8u lonu[9];
	
	float latdec;
	float londec;

	gsmmsg[0] = '\0';

	for (i = 0; i < 10; i++)
		lat[i] = lon[i] = '0';

	lat[10] = lon[10] = '\0';
	lat[0] = lon[0] = '\0';
	

	strcat(gsmmsg,GSMMsg);
	strcat(gsmmsg," http://maps.google.com/maps?q=");
	
	#ifdef DEMO
		strcat(gsmmsg,"12.2766");
		strcat(gsmmsg,",");
		strcat(gsmmsg,"76.62022");
	#else	
		GPSEn();
		GPSgetloc(lat,lon);
		
		#ifdef DISPLAY_LOC
			lcdclr();
			lcdws(lat);
			lcdr2();
			lcdws(lon);
			dlyms(10000);
			lcdclr();
		#endif 
		
			
		for (i = 0; i < 2; i++)
			latl[i] = lat[i];
			
		latl[i] = '\0';
		
		for (i = 2; i < 10; i++)
			latu[i-2] = lat[i];
			
		latu[i-2] = '\0';
		
			
		latdec = (atof(latl)) +  ((atof(latu)) / 60.0);
			
		ftoa(latdec, lat, 4);
	
		
		for (i = 0; i < 3; i++)
			lonl[i] = lon[i];
			
		lonl[i] = '\0';
			
		for (i = 3; i < 10; i++)
			lonu[i-3] = lon[i];
			
		lonu[i-3] = '\0';
			
		londec = atof(lonl) + ( atof(lonu) / 60.0 );
			
		ftoa(londec, lon,4);
		
					
		strcat(gsmmsg,lat);
		strcat(gsmmsg,",");
		strcat(gsmmsg,lon); 
		
	#endif
	
	GSMEn();
	GSMsndmsg(PhNum, gsmmsg);
}
ISR (USART_RXC_vect) {
	static int8u i;
	static int8u msgcnt,phcnt;
	static int8u state = MSG_WAIT_MSG;

	switch (state) {
		case MSG_WAIT_MSG:
		if ( UDR == '\"') state = MSG_PH_NUM;
		break;
		case MSG_PH_NUM:
		if (phcnt++ < 13)
		PhNum[phcnt-1] = UDR;
		else
		state = MSG_COLL_MSG;
		break;
		case MSG_COLL_MSG:
		if (UDR == LINE_FEED)
		state = MSG_RCV_MSG;
		break;
		case MSG_RCV_MSG:
		if ((sbuf[msgcnt++] = UDR) == LINE_FEED) {
			sbuf[msgcnt-2] = '\0';
			for (i = 0 ; i < 10; i++)	/* eliminate +91 */
			PhNum[i] = PhNum[i+3];
			PhNum[i] = '\0';
			state = MSG_WAIT_MSG;
			msgcnt = 0;
			phcnt = 0;
			Flags.Msg = TRUE;
			DisUARTInt();
		}
	}
}