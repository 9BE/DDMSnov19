/*
 * ais.h
 *
 *  Created on: Mar 14, 2019
 *      Author: annuar
 */

#ifndef AIS_H_
#define AIS_H_

#include 	<Arduino.h>

//union{
//  unsigned char all;
//  struct{
//    unsigned Door:1;    //real time
//    unsigned Ambient:2;   //dark=1 bright=dim=0
//    unsigned Lamp:2;
//    unsigned LanternBatt:2;
//    unsigned Beat:1;
//  };
//  struct{
//    unsigned impact:1;
//    unsigned gscale:2;
//  };
//}AtoNDigital;

class ais {

public:

	int checksum(String data);
	bool validate(String data);
	String getValue(String data, char separator, int index);


	void Message06(char * memory, long dest, int channel);
	void message6bits(long data, char nums, char * memory);
	void genEncData(char *memory);
	char sixChar(char data);

	int actual = 0;
	char buffer[768];

	int max = 3500;
	int min = 500;

	char mainPower;
	char open;
	float battery;
	char loaded;

	int hopperCount;

	int hopperA;
	int hopperB;

	int sonarCount;

};

#endif /* AIS_H_ */
