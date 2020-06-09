/*
 * LocSonar.h
 *
 *  Created on: Feb 7, 2020
 *      Author: suhaimi
 */

#ifndef OURS_LOCSONAR_H_
#define OURS_LOCSONAR_H_

#include "Arduino.h"
//#include "pins.h"
#include "digitalize.h"
#include "graph.h"
//#include "LocOLED.h"

class LocSonar {
public:
	LocSonar(int core, int loopDelay, HardwareSerial * locSerial, double Max, double Min);
	virtual ~LocSonar();

	void setEnable(bool enable = false) {
		_enable = enable;
		_done = false;

		if (enable) {
			_debugSOnar = "";
		}
//		if (enable) {
//			digitalWrite(OutB, HIGH);
//
//			if (this->_serial->baudRate() != 9600) {
//				this->_serial->updateBaudRate(9600);
//			}
//
//			digitalWrite(MUX_S1, HIGH);
//			digitalWrite(MUX_S0, LOW);
//
//			delay(100);
//
//			log_i("");
//
//			log_i("enable Sonar");
//		}else {
//			digitalWrite(OutB, LOW);
//
//			digitalWrite(MUX_S1, LOW);
//			digitalWrite(MUX_S0, LOW);
//
//			char cr;
//			while (this->_serial->available()) {
//				cr = this->_serial->read();
//			}
//
//			log_i("disable Sonar");
//		}
	}

//	void setOled(LocOLED* oled) {
//		_oOLED = oled;
//	}

	double getSonarDistance() const {
		return _sonarDistance;
	}

	bool isDone() const {
		return _done;
	}

	bool isEnable() const {
		return _enable;
	}

	const String& getDebugSOnar() const {
		return _debugSOnar;
	}

	uint32_t getMasaSonarSerial() const {
		return _masaSonarSerial;
	}

private:
	static void loop (void * param);
	int getNumber();
	boolean isNumeric(String & str);

	uint32_t _loopDelay;
	HardwareSerial * _serial;
	bool _enable = false;
	String _raw;
	String _debugSOnar = "";
	bool _done = false;
	double 	_sonarDistance;
	uint32_t _masaSonarSerial = 0;


	digitalize 		*digiSonar;
	graph			*graphSonar;

//	LocOLED		*_oOLED;
};

#endif /* OURS_LOCSONAR_H_ */
