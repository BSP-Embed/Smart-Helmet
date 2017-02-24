#ifndef SMS_H
#define SMS_H

//INCLUDE HEADER FILES
#include "includes.h"

#define MSG_WAIT_MSG	1
#define MSG_PH_NUM		2
#define MSG_COLL_MSG	3
#define MSG_RCV_MSG		4
#define LINE_FEED		0x0A

//FUNCTION PROTOTYPE

void GPSinit	(void);
void sendloc	(const char *PNum, const char *GSMMsg);
void SendOTP	(const char *PNum,const char *GSMMsg);
void SendLinkLoc(const char *PhNum, const char *GSMMsg);

#endif