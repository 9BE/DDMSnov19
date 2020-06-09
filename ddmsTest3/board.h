/*
 * board.h
 *
 *  Created on: Aug 6, 2018
 *      Author: annuar
 */

#ifndef BOARD_H_
#define BOARD_H_

#include	<ArduinoOTA.h>
#include	<WiFi.h>
#include "han.h"

#define pOutOnHopper 32		// v5->25 v6->32
#define pOutOnSonar 25  	// v5->32 v6->25
#define pOutOnWideLink 33

#define pOutDRes 21
#define pOutDDC 4
#define pOutDCS 5
#define pInHopperA 17
#define pInHopperB 16
#define pOutS0 27
#define pOutS1 14

#define pLEDStatus 22

#define pS0 27
#define pS1 14

//#define pPowerWidelink 33
//#define pPowerSonar 32
//#define pPowerHopper 25

#define pInMain 39

enum{
	none0,
	portHopper,
	portSonar,
	portWidelink
};


class board {
public:
	board();
	void getMAC();
	int getChannel();
	virtual ~board();

	char hopper1, hopper2, mains;

	String macID;
};

#endif /* BOARD_H_ */
