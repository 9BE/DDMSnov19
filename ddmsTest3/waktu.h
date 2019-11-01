/*
 * waktu.h
 *
 *  Created on: May 18, 2019
 *      Author: nas
 */

#ifndef WAKTU_H_
#define WAKTU_H_

#include "Arduino.h"

#define START_YEAR 1970

typedef struct{
	unsigned char saat;
	unsigned char minit;
	unsigned char jam;
}masa;

typedef struct{
	masa time;
	unsigned char hari;
	unsigned char bulan;
	unsigned int  tahun;
}dateTime;

void setTime(int hr,int min,int sec,int dy, int mnth, int yr);
//unsigned long toSecond(void);
int isleap(int year);
void localDateTime(dateTime *p, long utc, char offsetHour);


#endif /* WAKTU_H_ */
