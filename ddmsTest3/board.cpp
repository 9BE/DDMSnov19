/*
 * board.cpp
 *
 *  Created on: Aug 6, 2018
 *      Author: annuar
 */

#include "board.h"

board::board() {
	// TODO Auto-generated constructor stub

}

board::~board() {
	// TODO Auto-generated deconstructor stub
}


//=============================================================================
void board::getMAC(){
	uint8_t mac[6];
	WiFi.macAddress(mac);

	macID = "";


	uint8_t num;
	for(int i=0; i < 5; i++){
		num = mac[i];
		if(num < 16) macID += "0";
		macID += String(mac[i], HEX) + ":";
	}
	macID += String(mac[5], HEX);



	macID.toUpperCase();
	hantu("getMAC() - ");
	hantu(macID);
}


int board::getChannel(){
	bool found = false;
	int c = 0;

	int n = WiFi.scanNetworks();
	for (int i = 0; i < n; i++) {
		if(WiFi.channel(i) > 12){
			break;
		}

		if( c != WiFi.channel(i)){
			c++;
			if( c != WiFi.channel(i)){
				found = true;
				break;
			}
		}
	}

	if(!found){
		c = 1;
	}
	else{
		if(c == 0) c = 1;

	}
	return c;

}




