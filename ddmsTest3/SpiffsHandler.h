/*
 * SpiffsHandler.h
 *
 *  Created on: Jun 24, 2019
 *      Author: suhaimi
 */

#ifndef SPIFFSHANDLER_H_
#define SPIFFSHANDLER_H_

#include "Arduino.h"
#include "SPIFFS.h"
#include "ArduinoJson.h"
#include "han.h"

#define freshSetup false

class SpiffsHandler {
public:
	SpiffsHandler();
	virtual ~SpiffsHandler();
	bool writeToSpiffs(String whatToSave, String value);
	String readFromSpiffs(String whatToRead);
	void mulaFiles();
	void mulaFiles(bool mulai);
};

#endif /* SPIFFSHANDLER_H_ */
