/*
 * task1.cpp
 *
 *  Created on: May 18, 2019
 *      Author: nas
 */

#include "task1.h"

String receiveText="";
String nmea="";
String nmeahead="";

int GPSGap=0;

float Lat=0, Lng=0;

unsigned long lastAisSerial=0;
unsigned long lastSonarSerial=0;
unsigned long lastGPS=10;

bool flagToSend = false;
bool readyToSend = false;
bool dahSetGPS = false;
bool abk = false;

extern String nakDebug1;
extern ais Ais;
extern String task;
extern unsigned long unix;

extern bool waitDone;
extern bool tidur;

void ReadSerial(void)
{
	char cR;
	int x=0, y=0, z=0, start = 0, end = 0;
	String temp="";
	bool ada=false;

	while(Serial.available() > 0){

		if(task == "Sonar"){

//			if(isAlphaNumeric(cR)){
//				receiveText.concat(cR);
//				lastSonarSerial = unix;
//			}
		}
		else{
			cR = Serial.read();
			if (cR >= 32 && cR <= 126) {
				receiveText.concat(cR);
			}

			if (cR == 13) {
				receiveText.concat(cR);
			}

//			nmea.concat(cR);
			if(cR == '\n'){
//				nmea += receiveText;
//				nmea += "</br>";
				lastAisSerial = unix;
				ada=true;
			}
		}
	}

//	if(ada)nmea += receiveText + "</br>";

	//!AIVDO,1,1,,,B>eq`d@001l=N!AIVDO,1,1,,,B>eq`d@001l=N!AIVDO,1,1,,,B>eq`d@001l=N!AIVDM,1,1,,B,4055DOAv=@c:MWAtqN1uRG102@Ag,0*2D
	while(ada){
		if (task == "Sonar") {
			break;
		}

		if (task == "WideLink") {
			x = receiveText.indexOf('!',x);
			y = receiveText.indexOf('$',y);
			z = receiveText.indexOf('*',z);
			start = getSmallestValidNumber(x, y);
			if(start >= 0){
//				end = receiveText.indexOf('\n',start);
				z = receiveText.indexOf('*',start);
				end = -1;
				if (z >= 0) {
					end = z + 3;
					if (end >= receiveText.length()) {
						end = -1;
					}
				}

				if(end >= 0){
					temp = receiveText.substring(start,end);
					nmea += temp + "</br>";
					if(Ais.validate(temp)){
						esp_task_wdt_reset();
						readyToSend = true;
						if(IntrestInfo(temp)){
//							nmea += temp + "</br>";
						}
					}
					else{
						nmea += "Error-----------------------</br>";
					}

//					flagToSend = true;
//					readyToSend = false;
					receiveText = receiveText.substring(end);
				}
				else{
					nmea += "<hr>";
//					if(flagToSend){
//						flagToSend = false;
//						readyToSend = true;
//					}

					break;
				}
			}
			else{
				break;
			}
		}

	}

}

double toDegree(String snum)
{

	float num = snum.toFloat();

	float temp = num / 100;
	int a = (int) temp;			//holding deg int
	float b = temp - a;			//holding minute
	b *= 100;
	b /= 60;
	b += a;

	return b;
}

bool IntrestInfo(String test)
{
	bool res=false;

	if(test.indexOf("RMC,") >=0){
		res = true;
		if(Ais.getValue(test, ',', 2) == "A"){
			// 0     1         2 3          4 5           6 7     89
			//$GNRMC,070442.00,A,0305.37038,N,10132.77633,E,0.008,,300419,,,D*67
			//$GNRMC,193903.00,A,0305.37038,N,10132.77633,E,0.008,,180519,,,D*67

			String timeNmea = Ais.getValue(test, ',', 1);
			String dateNmea = Ais.getValue(test, ',', 9);
			String sLat = Ais.getValue(test, ',', 3);
			String sLng = Ais.getValue(test, ',', 5);

			Lat = toDegree(sLat);
			Lng = toDegree(sLng);

			setTime(timeNmea.substring(0,2).toInt(), timeNmea.substring(2,4).toInt(), timeNmea.substring(4,6).toInt(), dateNmea.substring(0,2).toInt(), dateNmea.substring(2,4).toInt(), dateNmea.substring(4,6).toInt());
			GPSGap = 0;
			dahSetGPS = true;

		}
	}
	else if(test.indexOf("VDO,") >= 0){
		res = true;
	}
	else if(test.indexOf("VDM,") >= 0){
		res = true;
	}
	else if(test.indexOf("ABK,") >= 0){
		res = true;
		String V = Ais.getValue(test, ',', 5);
		V = V.substring(0,1);
		if(V == "0"){
			hantu(" YEAAAAAAAA "  );
			abk = true;
		}

	}

	if(res) {
		nmeahead = Ais.getValue(test, ',', 0);	// take only the first header ?
	}

	return res;
}

int getSmallestValidNumber(int a, int b)
{
	int result=0;
	// if result = -1 both a & b = -1

	if((a >= 0) && (b >= 0)){
		if(a > b){
			result = b;
		}
		else{
			result = a;
		}
	}
	else{
		if((a < 0) && (b < 0)){
			result = -1;
		}
		else{
			if(a >= 0){
				result = a;
			}
			if(b >= 0){
				result = b;
			}
		}
	}

	return result;
}

void codeForTask1(void * parameter)
{

	while(1){
		// Your code runs here b4 delay

		if (waitDone) ReadSerial();
		if (tidur) esp_task_wdt_reset();

		if(GPSGap > 50){
			dahSetGPS = false;
		}

		if (!Ais.open) {
			nmea = "";
		}

		nakDebug1 = "Task1 complete on core ";
		nakDebug1 += String(xPortGetCoreID());
		nakDebug1 += " at ";
		nakDebug1 += millis();

		esp_task_wdt_reset();


		delay(10);
	}
}
