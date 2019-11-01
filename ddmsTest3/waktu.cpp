#include "waktu.h"

dateTime now;

unsigned long unix;

const char days_month[2][12] = {
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

void setTime(int hr,int min,int sec,int dy, int mnth, int yr)
{
	int i;
	long temp;

	temp = 0;
	yr += 2000;

	for(i=START_YEAR ; i < yr ; i++ ) {
		temp += isleap(i) ? 366 : 365;
	}

	for(i=0 ; i < mnth - 1; i++ ) {
		temp += days_month[isleap(yr)][i];
	}
	temp += dy - 1;
	temp *= 86400L;
	temp += hr * 3600L;
	temp += min * 60L;
	temp += sec;

	unix = temp;

}

void localDateTime(dateTime *p, long utc, char offsetHour) //@#$%@#$%@#$%@#$%@#$% SUN.C @#$%@#$%@#$%@#$%@#$%@#$%@#$%
{
	long days, j;
	int i = START_YEAR;
	int k;
	char hb;

	masa *jj;

	jj = &p->time;


	utc += offsetHour * 3600;				// Correct for TZ/DST offset	//1450153545
	days = utc / 86400;						// Integer number of days	//16784
	j = utc % 86400;						// Fraction of a day			//15945
	jj->jam = j /3600;						// Integer number of hours
	j %= 3600;								// Fraction of hour
	jj->minit = j / 60;						// Integer number of minutes
	jj->saat = j % 60;						// Remainder seconds

	// Count the number of days per year taking in account leap years
	// to determine the year number and remaining days
	while(days >= (j = isleap(i) ? 366 : 365) ) {
		i++;
		days -= j;
	}

	p->tahun = i;							// We have the year

	i = isleap(i);
	// Count the days for each month in this year to determine the month


	k = 0;
	while(1){
		hb = days_month[i][k];
		if(days >= hb){
			days = days - hb;
		}
		else{
			break;
		}
		k = k + 1;
	}

	k = k + 1;

	p->bulan = (char)k;							// We have the month
	p->hari = days + 1;						// And the day of the month
}

int isleap(int year) //@#$%@#$%@#$%@#$%@#$% SUN.C @#$%@#$%@#$%@#$%@#$%@#$%@#$%
{
	char y;

	y = (( year % 4 == 0 ) && ( year % 100 != 0 || year % 400 == 0 ));
	return(y);

}

//unsigned long toSecond(void) //@#$%@#$%@#$%@#$%@#$% SUN.C @#$%@#$%@#$%@#$%@#$%@#$%@#$%
//{
//	int i;
//	long temp;
//
//	temp = 0;
//	for(i=START_YEAR ; i < now.tahun ; i++ ) {
//		temp += isleap(i) ? 366 : 365;
//	}
//
//	for(i=0 ; i < now.bulan - 1; i++ ) {
//		temp += days_month[isleap(now.tahun)][i];
//	}
//	temp += now.hari - 1;
//	temp *= 86400L;
//	temp += now.time.jam * 3600L;
//	temp += now.time.minit * 60L;
//	temp += now.time.saat;
//
//
//	return temp;
//}
