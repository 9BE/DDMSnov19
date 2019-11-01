/*
 * task0.cpp
 *
 *  Created on: May 18, 2019
 *      Author: nas
 */

#include "task0.h"
#include "Arduino.h"

SSD1306Spi display(pOutDRes, pOutDDC, pOutDCS); // @suppress("Abstract class cannot be instantiated")
OLEDDisplayUi ui ( &display );

int screenW = 128;
int screenH = 64;
int clockCenterX = screenW/2;
int clockCenterY = ((screenH-16)/2)+16;   // top yellow part is 16 px height
int clockRadius = 23;

FrameCallback framesSonar[] = { titleFrame, typeA, typeB };
FrameCallback framesSonarHopper[] = { titleFrame, typeA, typeB, typeC };
FrameCallback framesHopper[] = { titleFrame, typeA, typeC };
//FrameCallback frames[] = { typeB };
int frameCount = 3;
//int frameCount = 1;
const int spacing = 12;

char infoToDisplay[6][24];
//bool core0ProceedFlag = true;
bool displayProceedFlag = true;

extern String nakDebug0;
extern ais Ais;

//extern int GPSGap;
extern bool dahSetGPS;
extern dateTime now;
extern unsigned long unix;
extern unsigned long lastAisSerial;
extern String nmeahead;
extern unsigned long lastSonarSerial;

int rawBattery = 0 ;
float bat=0;
float adcBattery = 0;

bool freshOpen=false;
bool requestSetupWifi = false;
bool freshClose=true;

extern int adcMain;

extern WebServer server;

extern bool tidur;

int j = 99;
unsigned long jj=0;

void typeC(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y)
{
	String text = "";
	int offY = 0;

	display->setTextAlignment(TEXT_ALIGN_LEFT);
	display->setFont(ArialMT_Plain_10);


	text = "Hopper Count : ";
	text += Ais.hopperCount;
	offY += spacing;
	display->drawString(x ,  y + offY , text );

	text = "Hopper A : ";
	text += Ais.hopperA;
	offY += spacing;
	display->drawString(x ,  y + offY , text );

	text = "Hopper B : ";
	text += Ais.hopperB;
	offY += spacing;
	display->drawString(x ,  y + offY , text );


	display->drawString(87 ,  0 , nmeahead );

	String timenow = twoDigits(now.time.jam)+":"+twoDigits(now.time.minit)+":"+twoDigits(now.time.saat);
	if(!dahSetGPS){
		timenow = "NO GPS";
	}
	display->drawString(0 , 0, timenow );
}

void bye(void)
{
	display.clear();
	String txt = "Byeee.....";
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.setFont(ArialMT_Plain_16);
	display.drawString(10, 10, txt);
	display.display();
	delay(500);
	display.clear();
	display.displayOff();
	delay(5);
}

void setupDisplay(void)
{
	ui = &display;

	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.setFont(ArialMT_Plain_10);

	ui.setTargetFPS(60);
	ui.setActiveSymbol(activeSymbol);
//	ui.setInactiveSymbol(inactiveSymbol);
//	ui.setIndicatorPosition(TOP);
//	ui.setIndicatorDirection(LEFT_RIGHT);
	ui.setFrameAnimation(SLIDE_LEFT);
	if (Ais.sonarCount && Ais.hopperCount) ui.setFrames(framesSonarHopper, frameCount+1);
	else if (Ais.hopperCount) ui.setFrames(framesHopper, frameCount);
	else ui.setFrames(framesSonar, frameCount);
	ui.disableAllIndicators();
	ui.enableAutoTransition();

}

void typeB(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y)
{
	String text = "";
	int offY = 0;
	int mid;

	display->setTextAlignment(TEXT_ALIGN_LEFT);
	display->setFont(ArialMT_Plain_10);

	mid = Ais.max + Ais.min;
	mid /= 2;

	text = "Load : ";

	if(Ais.actual > mid){
		text += "Empty";
	}
	else{
		text += "Loaded";
	}

	text += "        ";
	if(unix - lastSonarSerial > 30){
		text += "NG";
	}
	else {
		text += "OK";
	}


	offY += spacing;
	display->drawString(x ,  y + offY , text );

	text = "Max : ";
	text += String(Ais.max);
	offY += spacing;
	display->drawString(x ,  y + offY , text );

	text = "Min : ";
	text += String(Ais.min);
	offY += spacing;
	display->drawString(x ,  y + offY , text );

	text = "Actual : ";
	text += String(Ais.actual);

	offY += spacing;
	display->drawString(x ,  y + offY , text );


	display->drawString(87 ,  0 , nmeahead );

	String timenow = twoDigits(now.time.jam)+":"+twoDigits(now.time.minit)+":"+twoDigits(now.time.saat);
	if(!dahSetGPS){
		timenow = "NO GPS";
	}
	display->drawString(0 , 0, timenow );
}

void typeA(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y)
{
	String text = "";
	int offY = 0;

	display->setTextAlignment(TEXT_ALIGN_LEFT);
	display->setFont(ArialMT_Plain_10);

	text = "RS422 : ";

	if(unix - lastAisSerial > 20){
		text += "NG ";
		if(tidur)nmeahead = "SLEEP";
		else nmeahead = "";
	}
	else{
		text += "OK ";
	}

	text += "        ";


	if(Ais.mainPower == 1){
		text += "Powered";
	}
	else{
		text += "Battery";
	}


	offY += spacing;
	display->drawString(x ,  y + offY , text );

	text = "Battery : ";
	text += bat;

	offY += spacing;
	display->drawString(x ,  y + offY , text );

	text = "Door : ";
	if(DoorClose()){
		text += "Close";
	}
	else{
		text += "Open";
	}

	offY += spacing;
	display->drawString(x ,  y + offY , text );

	display->drawString(87 ,  0 , nmeahead );

	String timenow = twoDigits(now.time.jam)+":"+twoDigits(now.time.minit)+":"+twoDigits(now.time.saat);
	if(!dahSetGPS){
		timenow = "NO GPS";
	}
	display->drawString(0 , 0, timenow );

}

void titleFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y)
{

	String txt = "";

	txt = "SPMS V5.0";
	display->setTextAlignment(TEXT_ALIGN_CENTER);
	display->setFont(ArialMT_Plain_24);
	display->drawString(clockCenterX + x , clockCenterY/2 + y, txt );

	txt = "GreenFinder";
	display->setFont(ArialMT_Plain_16);
	display->drawString(clockCenterX + x , clockCenterY + y, txt );

	display->setTextAlignment(TEXT_ALIGN_LEFT);
	display->setFont(ArialMT_Plain_10);

	display->drawString(87 ,  0 , nmeahead );

	String timenow = twoDigits(now.time.jam)+":"+twoDigits(now.time.minit)+":"+twoDigits(now.time.saat);
	if(!dahSetGPS){
		timenow = "NO GPS";
	}
	display->drawString(0 , 0, timenow );
}

// utility function for digital clock display: prints leading 0
String twoDigits(int digits)
{
	if(digits < 10) {
		String i = '0'+String(digits);
		return i;
	}
	else {
		return String(digits);
	}
}


void enterLine(String s)
{
	int i;
	display.clear();
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.setFont(ArialMT_Plain_10);

	for(i=0; i < 5; i++){
		// 0 1 2 3 4
		memcpy(infoToDisplay[i], infoToDisplay[i+1], 24);
		display.drawString(0, i*10, infoToDisplay[i]);
	}
	s.toCharArray(infoToDisplay[5], 30);
	display.drawString(0, i*10, infoToDisplay[i]);
	display.display();
}

void UiInit()
{
	display.displayOn();
	ui = &display;
	ui.init();
	display.flipScreenVertically();

}

bool DoorClose()
{
	bool result=false;

	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_2_5);
	int val = adc1_get_raw(ADC1_CHANNEL_0);

	if(val > 1000){
		result = true;
		Ais.open = 0;
		freshOpen = true;

//		if (freshClose) {
//			freshClose = false;
//			WiFi.softAPdisconnect(true);
//			WiFi.disconnect(0, 0);
//			server.stop();
//			displayProceedFlag = false;
//			bye();
//		}

	}
	else{
		Ais.open = 1;
		freshClose = true;

		if(freshOpen){
			freshOpen = false;
			requestSetupWifi = true;
			displayProceedFlag = true;
		}
	}


	return result;
}

void BatteryPower()
{
	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_11);
	rawBattery = adc1_get_raw(ADC1_CHANNEL_6);

	adcBattery = rollAverage(adcBattery, rawBattery, 200);

	bat = adcBattery * 0.0097664544; 	//0.0093154552;
	bat += 1.8104458599;				//1.8175354745;
}

bool MainPower()
{
	bool result=false;

	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(ADC1_CHANNEL_3,ADC_ATTEN_DB_11);
	int val = adc1_get_raw(ADC1_CHANNEL_3);

	Ais.battery = bat;
	adcMain = val;

	if(val < 1000){
		Ais.mainPower = 1;
		result = true;
	}
	else{
		Ais.mainPower = 0;
	}
	return result;
}

float rollAverage(float prev, float newData, float roll)
{
	float X;
	X = prev * roll;
	X -= prev;
	X += newData;
	X /= roll;
	return X;
}

void codeForTask0(void * parameter)
{
	UiInit();
	setupWiFi();
	setupDisplay();
	esp_task_wdt_reset();

	while(1){
		// Your code runs here b4 delay

		if (Ais.open) server.handleClient();

		if(requestSetupWifi){
			requestSetupWifi = false;
			UiInit();
			setupWiFi();
			setupDisplay();
		}

		if (displayProceedFlag) {
			int remainingTimeBudget = ui.update();

			if (remainingTimeBudget > 0) {
				esp_task_wdt_reset();
				delay(remainingTimeBudget);
				esp_task_wdt_reset();
			}

		}

		DoorClose();
		BatteryPower();
		MainPower();

		nakDebug0 = "Task0 complete on core ";
		nakDebug0 += String(xPortGetCoreID());
		nakDebug0 += " at ";
		nakDebug0 += millis();

		esp_task_wdt_reset();
		delay(10);
	}


}



