#include "Arduino.h"
#include "all.h"

#define tickInterval 1000
#define DEBUG true

TaskHandle_t Task0;
TaskHandle_t Task1;

ais Ais;
timer Timer;

String nakDebugSonar="";
String nakDebugLoop="";
String nakDebug0="";
String nakDebug1="";
String nakDebug="";
String task="";
String sentMsg6="";

char channel=1;

int hantarGunaBatt=0;

unsigned long sensorTime=10;
unsigned long aisTime=10;
unsigned long battTime=10;
unsigned long hopperTime=0;
unsigned long lastMsg6Sent=0;
unsigned long lastSonarRead=0;

int battInterval=0;

//extern WebServer server;
extern String receiveText;
extern dateTime now;
extern int GPSGap;

extern bool readyToSend;
extern bool dahSetGPS;
extern bool abk;

extern unsigned long unix;

bool freshBat = true;
bool yeayyy = false;

int adcMain=0;

bool waitDone=false;

bool hi=false;
unsigned long ledTime=0;

int abkCtr = 0;

bool tidur = false;
unsigned long tidurSelama = 0;


int readingHopperA = 0;
int readingHopperB = 0;

JsonHandler *jsonHandler;
SpiffsHandler *spiffsHandler;

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here


	Serial.begin(115200);
	Serial.println("MULAI . . . . .");

	waitDone = false;

	pinMode(pOutOnHopper, OUTPUT);
	pinMode(pOutOnSonar, OUTPUT);
	pinMode(pOutOnWideLink, OUTPUT);
	digitalWrite(pOutOnHopper, HIGH);
	digitalWrite(pOutOnSonar, HIGH);
	digitalWrite(pOutOnWideLink, HIGH);

	pinMode(pOutS0, OUTPUT);
	pinMode(pOutS1, OUTPUT);
	digitalWrite(pOutS0, LOW);
	digitalWrite(pOutS1, LOW);


	pinMode(pInHopperA, INPUT);
	pinMode(pInHopperB, INPUT);
	pinMode(pLEDStatus, OUTPUT);
	pinMode(pS0, OUTPUT);
	pinMode(pS1, OUTPUT);
	pinMode(pInMain, INPUT);

	pinMode(2, OUTPUT);

	xTaskCreatePinnedToCore(codeForTask0, "task_0", 5000, NULL, 1, &Task0, 0);
	xTaskCreatePinnedToCore(codeForTask1, "task_1", 5000, NULL, 1, &Task1, 1);

	Timer.tick = tickInterval;
	unix = 0;


	jsonHandler = new JsonHandler;
	spiffsHandler = new SpiffsHandler;

	spiffsHandler->mulaFiles();

	Ais.sonarCount = spiffsHandler->readFromSpiffs("sonar").toInt();
	Ais.min = spiffsHandler->readFromSpiffs("min").toInt();
	Ais.max = spiffsHandler->readFromSpiffs("max").toInt();
	Ais.hopperCount = spiffsHandler->readFromSpiffs("hopper").toInt();

	jsonHandler->mID = spiffsHandler->readFromSpiffs("m");
	jsonHandler->mName = spiffsHandler->readFromSpiffs("n");
//	jsonHandler->mGroup = spiffsHandler->readFromSpiffs("g");


	esp_task_wdt_init(60, true);
	enableLoopWDT();

	esp_task_wdt_add(Task1);
	esp_task_wdt_add(Task0);


//	String temp = "{\"d\":\"GreenFinderIOT\",\"b\":\"CC:50:E3:B6:C6:DD\",\"m\":\"WF7TDK\",\"n\":\"Mando Pro\",\"j\":\"g\",\"u\":0,\"tabs\":{\"1\":\"Update List\"},\"rows\":[{\"tab\":1,\"row\":6,\"type\":\"2\",\"element\":[{\"e1\":[\"Group\"],\"i\":9},{\"e2\":[\"GF7TDK\",\"G1OFJV\"],\"i\":10}]}],\"T\":1562424896,\"P\":\"351542063657775\"}";
//	jsonHandler->processAdTech(temp);
	hantu("m==" + jsonHandler->mID);

	for (int i=1; i<=5; i++) {
		digitalWrite(2, HIGH);
		delay(i*5);
		digitalWrite(2, LOW);
		delay(i*5);
	}

	SelectPort(none0);
	SelectPort(portWidelink);


//	digitalWrite(pOutOnHopper, HIGH);

}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here

	Timer.test();
	if (Timer.tock) {
		Timer.tock = 0;
		unix++;
		if (!tidur) GPSGap++;
		localDateTime(&now, unix, 8);
	}

	if (Ais.mainPower) {
		runOnPowered();
	}else {
		runOnBattery();
	}

	if (!Ais.open) {
		nakDebug = "";
	}



	nakDebugLoop = "Loop complete on core ";
	nakDebugLoop += String(xPortGetCoreID());
	nakDebugLoop += " at ";
	nakDebugLoop += millis();

	delay(50);
}

void interruptReboot()
{
	SelectPort(none0);
	ESP.restart();
	esp_task_wdt_init(1, true);
	while(1) {}
}

void runOnBattery()
{
	if (unix - battTime >= battInterval) {
		if (freshBat) {
			if (tidur) {
				interruptReboot();
			}

			SelectPort(portWidelink);

			freshBat = false;
//			readyToSend = false;
//			dahSetGPS = false;
			nakDebug = "";
			abkCtr = 0;
			hantarGunaBatt = 0;

			SelectPort(portWidelink);

		}

		if (hantarGunaBatt < 10) { // asal 5
			if (readyToSend && dahSetGPS) {
				esp_task_wdt_reset();
				battTime = unix;
				battInterval = 60;  // asal 60

				if (Ais.sonarCount) {
					nakDebug += "s,";
					connectSonar();
					lastSonarRead = unix;

					delay(1000);
				}

				if (Ais.hopperCount) {
					connectHopper();
				}

				nakDebug += "ab";
				hantarAiS();
				lastMsg6Sent = unix;
				if (yeayyy) abkCtr++;
			}
		}

		if (hantarGunaBatt == 10) {

			esp_task_wdt_reset();
			nakDebug += ".";
			freshBat = true;
			tidur = true;
			delay(10000);
			SelectPort(none0);
			battTime = unix;
			battInterval = 1800; // asal 3600 / 1800 / 900
			waitDone = false;
		}
	}else {
		if (tidur) {
			tidurSelama = battTime + battInterval - unix;
			nakDebug = "sleep for ";
			nakDebug += String(tidurSelama);
			nakDebug += " sec";
		}
	}
}

void runOnPowered()
{
	if (!freshBat) nakDebug = "";

	if (unix - sensorTime >= 10) {
		if (Ais.sonarCount) {
			sensorTime = unix;
			nakDebug += "s,";
			connectSonar();
			lastSonarRead = unix;
		}

		if (Ais.hopperCount) {
			connectHopper();
		}
	}


	if (unix - aisTime >= 60 && readyToSend && dahSetGPS) {
		aisTime = unix;
		nakDebug += "a";
		hantarAiS();
		lastMsg6Sent = unix;
	}

	freshBat = true;
	tidur = false;
	abkCtr = 0;

	if (millis() >= 7200000) { //7200
		interruptReboot();
	}
}

void connectHopper()
{

	digitalWrite(pOutOnHopper, HIGH);
	delay(1000);

	if (digitalRead(pInHopperA)) Ais.hopperA = 0;
	else Ais.hopperA = 1;

	if (digitalRead(pInHopperB)) Ais.hopperB = 0;
	else Ais.hopperB = 1;

	digitalWrite(pOutOnHopper, LOW);

}

void SelectPort(byte port)
{
	char cR;
	waitDone = false;
	digitalWrite(pS0, 0);	//LSB	S0
	digitalWrite(pS1, 0);	//MSB	S1

	delay(100);

	while(Serial.available() > 0){
		cR = Serial.read();
	}

	receiveText="";

	digitalWrite(pS0, bitRead(port,0));	//LSB	S0
	digitalWrite(pS1, bitRead(port,1));	//MSB	S1

	if(port == portWidelink){
		digitalWrite(pOutOnWideLink, HIGH);
		digitalWrite(pOutOnSonar, LOW);
		Serial.updateBaudRate(4800);
		task = "WideLink";
	}
	else if(port == portSonar){
		digitalWrite(pOutOnSonar, HIGH);
		Serial.updateBaudRate(9600);
		task = "Sonar";
	}
	else if(port == portHopper){
		digitalWrite(pOutOnHopper, LOW);
		digitalWrite(pOutOnHopper, HIGH);
		task = "Hopper";
	}
	else if(port == none0){
		digitalWrite(pOutOnSonar, LOW);
		digitalWrite(pOutOnWideLink, LOW);
		digitalWrite(pOutOnHopper, LOW);
		task = "none0";
	}

	delay(500);
	receiveText="";
	waitDone = true;
}

void playLedStatus(int x, int onTime, int offTime)
{
	for (int i=0; i<x; i++) {
		digitalWrite(pLEDStatus, HIGH);
		delay(onTime);
		digitalWrite(pLEDStatus, LOW);
		delay(offTime);
	}
}

boolean isNumeric(String str)
{
    unsigned int stringLength = str.length();
    boolean seenDecimal = false;

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

float getDistance(String data)
{
	int Start = 0, Found=0;
	int reading[36], i=0;
	String Temp="";

	int max=0, min=9999;
	long jumlah=0;

	do{
		Found = data.indexOf("R",Start);  // asal
		if(Found >= 0){
			Temp = data.substring(Found+1,Found + 5);

			if(Temp.length() == 4 && isNumeric(Temp)){
				reading[i] = Temp.toInt();
				i++;
				reading[i] = 0;
			}
			Start = Found + 3;
		}
	}while(Found >= 0);

	if(i > 4){
		int y;
		for(y = 0; y < i; y ++){

			if(reading[y] == 0) break;
			//get max
			if(reading[y] > max) max = reading[y];

			//get min
			if(reading[y] < min) min = reading[y];

			//get total
			jumlah += reading[y];
		}
		//get average
		jumlah /= y;
//		Serial.println(jumlah);
		Ais.actual = jumlah;
	}
	return 0;
}

void connectSonar()
{
	digitalWrite(pLEDStatus, HIGH);
	SelectPort(portSonar);

	delay(3000);

	nakDebugSonar = receiveText;
	if(receiveText!="") getDistance(receiveText);

	digitalWrite(pLEDStatus, LOW);
	SelectPort(portWidelink);
}

void hantarAiS()
{

	readyToSend = false;
	if(channel == 1){
		channel = 2;
		Ais.Message06(Ais.buffer,701,1);
	}
	else{
		channel = 1;
		Ais.Message06(Ais.buffer,701,2);
	}


	sentMsg6 = Ais.buffer;
	Serial.print(Ais.buffer);
	Serial.print("\r\n");
	Serial.flush();
	delay(1);

	if(Ais.mainPower == 0) hantarGunaBatt++;
	nakDebug += "-,";


	playLedStatus(5, 10, 10);

	long hantar=0;

	while(true){
		yeayyy = false;
		hantar ++;
		if(abk){
			abk = false;
			playLedStatus(3, 100, 100);
			yeayyy = true;
			break;
		}
		if(hantar > 500){
			break;
		}

		delay(10);
	}

}

void hantu(String txt)
{

#ifdef DEBUG
	waitDone = false;
	uint32_t lastBaud = Serial.baudRate();
	Serial.updateBaudRate(921600);
	delay(1);
	Serial.println(txt);
	Serial.flush();
	delay(1);
	Serial.updateBaudRate(lastBaud);
	delay(1);
	waitDone = true;
#endif
}


