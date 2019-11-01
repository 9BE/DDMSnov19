/*
 * ais.cpp
 *
 *  Created on: Mar 14, 2019
 *      Author: annuar
 */

#include "ais.h"



//
//int Seq = 0;

//	Ais.Message06(Ais.buffer,701,3);
void ais::Message06(char * memory, long dest, int channel)
{

	// !AIABM,1,1,0,701,1,6,8DmT1CqeL`H,3*33

	char *p;
	char hh[12];
	int mid;

	memory[0] = 0x00;

//	actual += 20;


	message6bits(133,10,memory);  //DAC DAC=133 FI=12                 //OK
	message6bits(13,6,memory);    //FI                                //OK

	message6bits(max/20,9,memory);  //empty > full                  //OK
	message6bits(min/20,9,memory); //                            //OK
	message6bits(actual/20,9,memory); //empty > actual > full         //OK

	mid = (max+min)/2;

//	Serial.print("mid=");
//	Serial.print(mid);
//
//	Serial.print(" actual=");
//	Serial.print(actual);

	/*
	 * kalau actual < mid = loaded
	 *
	 *
	 *
	 * */

	if(actual > mid){
		loaded = 1;
		Serial.println(" Empty");
	}
	else{
		loaded = 0;
		Serial.println(" Load");
	}

	message6bits(mainPower,1,memory);  //main supply
	message6bits(loaded,1,memory);  //if more than half full
	message6bits(open,1,memory);  //casing open

	message6bits(battery*20,9,memory);  //Actual battery

	//===================================================



	message6bits(1,2,memory); //sonar
	//===================================================

	//  sonarStatus =5;
	//  message6bits(sonarStatus,4,memory); //number of hopper
	message6bits(hopperCount,4,memory); //number of hopper
	//===================================================
	message6bits(hopperA,1,memory); //hopper 1
	message6bits(hopperB,1,memory); //hopper 2

	genEncData(memory);

	p = &memory[512];
	strcpy(p, memory);

	strcpy(memory,"!AIABM,1,1,0,");

	ltoa(dest,hh,10);        //pembetulan

	strcat(memory,hh);
	strcat(memory,",");
	ltoa(channel,hh,10);
	strcat(memory,hh);
	strcat(memory, ",6,");
	strcat(memory , p);

	String base(memory);
	base = base.substring(1);
	int resultCS = checksum(base);
	String calculate = String(resultCS,HEX);
	if(calculate.length()==1){
		calculate = "0" + calculate;
	}

	calculate.toUpperCase();
	calculate.toCharArray(hh, 3);
	strcat(memory, "*");
	strcat(memory, hh);
}

int ais::checksum(String data)
{
	int c = 0;
	char t;

	for(int i= 0; i < data.length(); i++){
		t = data.charAt(i);
		if(t == '!'){
			t = 0;
		}
		if(t == '$'){
			t = 1;
		}
		c ^= t;
	}
    return c;
}


bool ais::validate(String data)
{
	int f, resultCS=0, x=0;
	String calculate="";
	bool result=false, pass=false;

	String testCS="";

	data.trim();
	String test = data.substring(1);

	x = data.indexOf("!",3);
	if(x > 0){
		result = false;
		pass = true;
	}

	x = data.indexOf("$",3);
	if(x > 0){
		result = false;
		pass = true;
	}

	//!AIVDO,1,1,,,B>eq`d@001l=N!AIVDO,1,1,,,B>eq`d@001l=N!AIVDO,1,1,,,B>eq`d@001l=N!AIVDO,1,1,,,B>eq`d@001l=N$GNRMC,070415.00,A,0305.37072,N,10132.77692,E,0.003,,260419,,,D*6C
	//!AIVDO,1,1,,,B>eq`d@001l=N!AIVDO,1,1,,,B>eq`d@001l=N$GNRMC,072014.00,A,0305.37058,N,10132.77695,E,0.003,,260419,,,D*64
	//!AIVDM,2,1,1,B,58155>p2>ktEKLhSL00<50F0I84pdhTp0000001?C`><=5!AIVDM,2,2,1,B,00000000000,2*26
	//!AIVDO,1,1,,,B>eq`d@001l=N!AIVDO,1,1,,,B>eq`d@001l=N!AIVDO,1,1,,,B>eq`d@001l=N!AIVDO,1,1,,,B>eq`d@001l=N<0LB@;Q3wjPl000,0*6D


	f = data.indexOf("*");
	if(f>=0 && pass==false){
		testCS = test.substring(f);
		test = test.substring(0,f-1);
		resultCS = checksum(test);

		calculate = String(resultCS,HEX);
		calculate.toUpperCase();

		if(calculate.length()==1){
			calculate = "0" + calculate;
		}

//		Serial.println(testCS + "-" + calculate);

		if(calculate == testCS){
			result = true;

		}
	}




	return result;
}

// https://stackoverflow.com/questions/9072320/split-string-into-string-array
String ais::getValue(String data, char separator, int index)
{
	int found = 0;
	int strIndex[] = {0, -1};
	int maxIndex = data.length()-1;

	for(int i=0; i<=maxIndex && found<=index; i++){
		if(data.charAt(i)==separator || i==maxIndex){
			found++;
			strIndex[0] = strIndex[1]+1;
			strIndex[1] = (i == maxIndex) ? i+1 : i;
		}
	}
	return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}




char ais::sixChar(char data)
{
  if(data < 0x28){
    data += 0x30;
  }
  else{
    data += 0x38;
  }
  return data;
}


void ais::genEncData(char *memory)
{
	int base = 0;
	int offset = 0;
	char sixbits;
	char bitfill = 0;
	char last = 0;
	char fill;

	while(1){
		sixbits = 0x00;
		for(offset=0; offset < 6; offset++){
			if(memory[(base*6)+offset] == 0x00) {
				bitfill = 6 - offset;
				last = 1;
				break;    //offset == 4
			}
			sixbits = sixbits << 1;
			if(memory[(base*6)+offset] == '1'){
				sixbits |= 0x01;
			}
			else{
				sixbits &= 0xFE;
			}

			memory[(base*6)+offset] = 'x';
		}
		if(last){
			if(bitfill){
				for(fill=0; fill<bitfill; fill++){
					sixbits = sixbits << 1;
				}
			}
		}
		sixbits = sixChar(sixbits);
		memory[base] = sixbits;
		base ++;
		memory[base] = 0x00;

		if(last) break;
	}
	if(bitfill == 6) bitfill = 0;
	memory[base+0] = ',';
	memory[base+1] = sixChar(bitfill);
	memory[base+2] = 0x00;
}


void ais::message6bits(long data, char nums, char * memory)
{
	int x,y;
	long titik;

	titik = pow(2,nums);

	x = strlen(memory);

	for(y = x; y < x + nums; y++){
		data = data << 1;
		memory[y] = 0x30;
		if(titik & data){
			memory[y] |= 1;
		}
	}
	memory[y] = 0x00;
}

