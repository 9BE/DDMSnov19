/*
 * LocSonar.cpp
 *
 *  Created on: Feb 7, 2020
 *      Author: suhaimi
 */

#include "LocSonar.h"

LocSonar * iniSonar;

TaskHandle_t taskSonar;

extern unsigned long unix;

LocSonar::~LocSonar() {
	// TODO Auto-generated destructor stub
}

LocSonar::LocSonar(int core, int loopDelay, HardwareSerial* locSerial, double Max, double Min) {
	iniSonar = this;
	iniSonar->_loopDelay = loopDelay;
	iniSonar->_serial = locSerial;
	iniSonar->digiSonar = new digitalize(Max,Min);
	iniSonar->graphSonar = new graph(64);

	xTaskCreatePinnedToCore(iniSonar->loop, "taskSonar", 1024, NULL, 1, &taskSonar, core);
}

void LocSonar::loop (void * param) {
	char cr;
	uint32_t masaMula = 0;
	int32_t distance = 0;
	int RFound=0;
	uint8_t tempChar;

	while (1) {
		if (iniSonar->_enable) {
//			iniSonar->_debugSOnar = "";
			if (iniSonar->_serial->available()) {
				while (iniSonar->_serial->available()) {
					cr = iniSonar->_serial->read();

					if(cr >= 32 && cr <= 126 ){			//printable char only
						iniSonar->_raw.concat(cr);
						iniSonar->_debugSOnar.concat(cr);

					}

					if(cr == 'R'){

						distance = iniSonar->getNumber();
						iniSonar->_masaSonarSerial = unix;
					}

					if(distance > 0){
						RFound ++;

						tempChar = iniSonar->digiSonar->toChar(distance);
						iniSonar->graphSonar->add(tempChar);
					}

					if(RFound > 24 && !iniSonar->_done){
						RFound = 0;
//						iniSonar->setEnable(false);

						graph_t ddd = iniSonar->graphSonar->transferToHisto();

						iniSonar->_sonarDistance = iniSonar->digiSonar->toDouble(ddd.Point);
						iniSonar->_done = true;
//						iniSonar->_oOLED->sonarDistance = iniSonar->_sonarDistance;
						iniSonar->_raw = "";
					}


					if (millis() - masaMula >= 10000) {
						masaMula = millis();
//						iniSonar->setEnable(false);
						iniSonar->_done = true;
						log_i("sonar raw :: %s", iniSonar->_raw.c_str());
						iniSonar->_raw = "";
					}
				}

			}
			else if (millis() - masaMula >= 10000) {
				masaMula = millis();
//				iniSonar->setEnable(false);
				iniSonar->_done = true;
				iniSonar->_raw = "";
			}
		}else {
			masaMula = millis();

		}

		delay(iniSonar->_loopDelay);
	}
}

int LocSonar::getNumber() {
	int start=0, end=0, pos = 0, tempNum = 0;
	String Temp = "";
	start = iniSonar->_raw.indexOf("R",pos);
	if(start != -1){
		pos = start + 1;
		end = iniSonar->_raw.indexOf("R",pos);
		if(end != -1){
//			log_i("SONAR Raw \n %s", iniSonar->_raw.c_str());
			Temp = iniSonar->_raw.substring(start+1,end);

			Temp.trim();

			iniSonar->_raw = iniSonar->_raw.substring(start+1);
//			log_i("Temp = %s", Temp.c_str());

			if((Temp.length() > 0) && isNumeric(Temp)){
				tempNum = Temp.toInt();
				if((tempNum == 500) || (tempNum == 4999) || (tempNum == 9999)){
					tempNum = 0;
				}
			}
		}
	}


	return tempNum;
}

boolean LocSonar::isNumeric(String& str) {
	unsigned int stringLength = str.length();
	boolean seenDecimal = false;


	//    log_i("panjang = %d", stringLength);

	if (stringLength == 0) {
		return false;
	}

	for(unsigned int i = 0; i < stringLength; ++i) {
		if (isDigit(str.charAt(i))) {
			continue;
		}

		if (str.charAt(i) == '.') {
			if (seenDecimal) {
				return false;
			}
			seenDecimal = true;
			continue;
		}
		return false;
	}
	return true;
}
