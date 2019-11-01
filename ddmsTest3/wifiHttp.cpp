#include "wifiHttp.h"

board Board;
WebServer server(80);
WiFiMulti wifiMulti;

extern String nakDebugLoop;
extern String nakDebug0;
extern String nakDebug1;
extern String nakDebugSonar;
extern String nmea;
extern String sentMsg6;
extern String nakDebug;


extern float Lat, Lng;
extern bool readyToSend;

extern unsigned long lastAisSerial;
extern unsigned long lastMsg6Sent;
extern unsigned long lastSonarRead;
extern unsigned long lastSonarSerial;
extern unsigned long unix;

extern int hantarGunaBatt;
extern int rawBattery;
extern float bat;

extern ais Ais;

extern bool yeayyy;
extern bool dahSetGPS;

extern int adcMain;
extern int abkCtr;
extern int j;

extern JsonHandler *jsonHandler;
extern SpiffsHandler *spiffsHandler;

void setupServer(void)
{


}

bool adTech()
{
	hantu("================ adTech ====================");
	String msg = inputA;
	hantu("Configure ddms");
	if (server.args()==0) {
		msg.replace("[note]", "");
		msg.replace("[mID]", jsonHandler->mID);
		msg.replace("[mac]", Board.macID);
	}
	else {
		if (server.argName(0) == "clear") {
			spiffsHandler->mulaFiles(true);
			msg.replace("[mac]", Board.macID);
			msg.replace("[note]", "FS Cleared");
			msg.replace("[mID]", jsonHandler->mID);
		} else if (server.arg(0).length() < 6) {
			msg.replace("[mac]", Board.macID);
			msg.replace("[note]", "Require 6 digit alphanumeric id");
			msg.replace("[mID]", server.arg(0));
		}
		else {
			spiffsHandler->writeToSpiffs("m", server.arg(0));
			jsonHandler->mID = server.arg(0);
			msg.replace("[mac]", Board.macID);
			msg.replace("[note]", "Configuration sent.");
			msg.replace("[mID]", server.arg(0));
		}
	}
	server.send(200, "text/html", msg);

	return true;
}

void clearFile() {

	SPIFFS.begin();

	hantu("clearFile arg==" + server.args());

	String str, tmp;
	File root = SPIFFS.open("/", FILE_READ);
	File dir = root.openNextFile();
	while (dir) {
		str += dir.name();
		str += " / ";
		str += dir.size();
		str += "\r\n";

		tmp = dir.name();
		if (tmp.indexOf("json") > 0 || tmp.indexOf("txt") > 0) {
			str = "Delete - ";
			str += dir.name();
			SPIFFS.remove(dir.name());
		}

		hantu(str);
		dir = root.openNextFile();

	}

	spiffsHandler->mulaFiles();

}

//===============================================================
// setupWiFi
//===============================================================
void setupWiFi(void)
{
	char thisSSID[20];
	char thisPWD[20];
	bool ap = false;

	delay(10);
	enterLine("");
	enterLine("");
	enterLine("");
	enterLine("...");
	enterLine("...");

	strcpy(thisSSID,"GreenFinderIOT");
//	strcpy(thisPWD,"xadezcsw");
	strcpy(thisPWD,"0xadezcsw1");

	WiFi.mode(WIFI_MODE_APSTA); //Access Point mode

    wifiMulti.addAP("ideapad", "lenovo7890");
    wifiMulti.addAP("GF_Wifi_2.4GHz", "Gr33nF1nd3r2018");
    wifiMulti.addAP("AndroidAP", "efdx6532");
    wifiMulti.addAP("Realme 2", "12345678");

    enterLine("Connecting Wifi...");
    if(wifiMulti.run() == WL_CONNECTED) {
        enterLine(WiFi.SSID());
        hantu(WiFi.SSID());
    }

    Board.getMAC();

    int c;
	c = Board.getChannel();
	WiFi.softAP(thisSSID, thisPWD, c);    //Password length minimum 8 char

    if(WiFi.localIP().toString() == "0.0.0.0"){
    	int c;
    	WiFi.mode(WIFI_MODE_AP); // @suppress("Invalid arguments")
    	c = Board.getChannel();
    	WiFi.softAP(thisSSID, thisPWD, c);    //Password length minimum 8 char
    	ap = true;
    }

    server.on("/stat", WebServer::THandlerFunction(StatusViaWiFi)); // @suppress("Invalid arguments")

    //	server.on("/game", HTTP_GET, [](){
    //		server.sendHeader("Connection", "close");
    //		server.send(200, "text/html", GAME_page);});
    //
    //	server.on("/", HTTP_GET, []() {
    //		server.sendHeader("Connection", "close");
    //		server.send(200, "text/html", loginIndex);});

    server.on("/adTech", WebServer::THandlerFunction(adTech));

	server.on("/reboot", HTTP_GET, WebServer::THandlerFunction([]() {
		server.sendHeader("Connection", "close");
		server.send(200, "text/html", "done");
		delay(1000);
		ESP.restart();
		}));

	server.on("/clearfs", WebServer::THandlerFunction([]() {
//		server.sendHeader("Connection", "close");
		clearFile();
		adTech();
	}));

	server.on("/config", WebServer::THandlerFunction(handleConfDDMS));

	server.on("/ota", HTTP_GET, WebServer::THandlerFunction([]() {
		server.sendHeader("Connection", "close");
		server.send(200, "text/html", ota);}));

	server.on("/update", HTTP_POST, WebServer::THandlerFunction([]() {
		server.sendHeader("Connection", "close");
		server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
		delay(1000);
		ESP.restart();}),
			WebServer::THandlerFunction([]() {
			HTTPUpload& upload = server.upload();
			if (upload.status == UPLOAD_FILE_START) {
				Serial.printf("Update: %s\n", upload.filename.c_str());
				if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
					Update.printError(Serial);
				}
			}
			else if (upload.status == UPLOAD_FILE_WRITE) {
				/* flashing firmware to ESP*/
				if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
					Update.printError(Serial);
				}
			}
			else if (upload.status == UPLOAD_FILE_END) {
				if (Update.end(true)) { //true to set the size to the current progress
					Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
				}
				else {
					Update.printError(Serial);
				}
			}
		}));

	server.on("/nine", HTTP_POST, WebServer::THandlerFunction(nine));


	server.begin(80);                  //Start server
	MDNS.begin("nine");
	hantu("HTTP server started");

	String wifiMod = "WiFi enabled     ";
	wifiMod += ap ? "AP" : "AP_STA";

	enterLine(wifiMod);
	delay(3000);
}

bool nine()
{
	digitalWrite(2, HIGH);
	hantu("===================nine=================");

	String msg = ""; // kena tukarkan kepada Device Serial Number

	if (server.args() == 0) {
		serializeJsonPretty(jsonHandler->makeInit(), msg);
	}
	else {
		if (server.argName(0) == "full") {
			serializeJsonPretty(jsonHandler->makeJson(), msg);
		}
		else if (server.argName(0) == "submit") {
		  String res = server.arg("plain");
		  jsonHandler->processSubmitJSON(res);
		  serializeJsonPretty(jsonHandler->makeJson(), msg);
		  hantu(res);

		  /*
			  $ANACE,995339999,E2,1000,0,0,0,MANDO PRO GREEN,0010010101,R*1A
			  $ANACF,995339999,7,9100.0000,N,18100.0000,E,0,2087,2088,2087,2088,0,05,0,R*39
		  */
		}
		else if (server.argName(0) == "adTech") {

		}

	}


	server.send( 200, "application/json", msg );

	digitalWrite(2, LOW);
	return true;
}

//===============================================================
// StatusViaWiFi
//===============================================================
void StatusViaWiFi(void)
{
	hantu("StatusViaWiFi");
	String msg="";

	long rssi = WiFi.RSSI();

	msg  = "MAC = " + Board.macID + "</br>";
	msg += "IP = " + WiFi.localIP().toString() + "</br>";
	msg += "Live = " + String(millis()/1000) + "</br>";
	msg += "Time = " + String(unix) + "</br>";
	msg += "Pos = " + String(Lat,7) + "," + String(Lng,7) + "</br>";
	msg += "Battery = " + String(bat) + "(" + String(rawBattery) + ")</br>";
	msg += "Main adc = " + String(adcMain) + "</br>";
	msg += "Power source = ";
	msg += Ais.mainPower ? "powered" : "battery";
	msg += "</br>";
	msg += "RSSI = " + String(rssi) + "</br>";
	msg += "Actual = " + String(Ais.actual) + "</br>";
////	msg += "Temp = " + String((temprature_sens_read() - 32) / 1.8) + "</br>";
	msg += "============================================== DEBUG =====================================================</br>";
	msg += "Ready to send = " + String(readyToSend) + "</br>";
	msg += "Dah set gps = " + String(dahSetGPS) + "</br>";
	msg += "Activity = " + nakDebug + "</br>";
	if(nakDebug.length()>100) nakDebug = "";
	if(Ais.mainPower==0) {
		msg += "Sent on battery = " + String(hantarGunaBatt) + "</br>";
		msg += "Abk ctr = " + String(abkCtr) + "</br>";
	}
	msg += nakDebugLoop + "</br>";
	msg += nakDebug1 + "</br>";
	msg += nakDebug0 + "</br>";
	msg += String(j) + "</br>";

	msg += "Hopper A = " + String(Ais.hopperA) + "</br>";
	msg += "Hopper B = " + String(Ais.hopperB) + "</br>";

	msg += "============================================== SONAR SERIAL =====================================================</br>";
	msg += "Last SONARserial = " + String(lastSonarSerial) + " (" + String(unix-lastSonarSerial) + " sec ago)" + "</br>";
	msg += "Last connectSONAR = " + String(lastSonarRead) + " (" + String(unix-lastSonarRead) + " sec ago)" + "</br>";

	msg += "Sonar serial :: " + nakDebugSonar + "</br>";

	msg += "============================================== AIS SERIAL =====================================================</br>";
	msg += "Last AISserial = " + String(lastAisSerial) + " (" + String(unix-lastAisSerial) + " sec ago)" + "</br>";
	msg += "Last msg6 = " + String(lastMsg6Sent) + " (" + String(unix-lastMsg6Sent) + " sec ago)" + "</br>";
	msg += "Sent msg :: " + sentMsg6 + "</br>";
	msg += "Yeayyy ? " + String(yeayyy) + "</br>";


	msg += "<hr> >>>>>>>>>>> </br>";

	msg += nmea + "<hr>";


	nmea = "";

	server.sendHeader("Connection", "close");
	server.send(200, "text/html", msg);

	delay(50);

}

///* function #2 */
//String SendHTML(String minn, String maxx, String note){
//	String ptr = "<!DOCTYPE html> <html>\n";
//	ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
//	ptr +="<title>Configure DDMS</title>\n";
//	ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
//	ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
//	ptr +="h5 {color: #ff0000;margin: 50px auto 30px;}";
//	ptr +="input.html-text-box {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
//	ptr +=".button-on {background-color: #3498db;}\n";
//	ptr +=".button-on:active {background-color: #2980b9;}\n";
//	ptr +=".button-off {background-color: #34495e;}\n";
//	ptr +=".button-off:active {background-color: #2c3e50;}\n";
//	ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
//	ptr +="</style>\n";
//	ptr +="</head>\n";
//	ptr +="<body>\n";
//	ptr +="<h1>WELCOME TO GREENFINDER DDMS</h1>\n";
//	ptr +="<h3>Configure DDMS Device Using Access Point(AP) Mode</h3>\n";
//
//	ptr +="<h5>" + note + "</h5>\n";
//
//	ptr +="<form action=\"/config\" method=\"post\">\n";
//	ptr +="Min:\n";
//	ptr +="<br/>\n";
//	ptr +="<input type=\"number\" name=\"min\" value=\"" + minn + "\"maxlength=\"100\" />\n";
//	ptr +="<br/>\n";
//	ptr +="Max:\n";
//	ptr +="<br/>\n";
//	ptr +="<input type=\"number\" name=\"max\" value=\"" + maxx + "\"maxlength=\"100\" />\n";
//	ptr +="<br/>\n";
//	ptr +="<input type=\"submit\" value=\"Submit\" />\n";
//	ptr +="</form>\n";
//
//	ptr +="</body>\n";
//	ptr +="</html>\n";
//	return ptr;
//}

/* function #3 */
void handleConfDDMS() {
	String msg = inputB;
	hantu("========= handleConfDDMS =============");
	if (server.args()==0) {
//		msg = SendHTML(readFromSpiffs("min"), readFromSpiffs("max"), "");
//		msg = SendHTML(String(Ais.min), String(Ais.max), "");
		msg.replace("[minn]", String(Ais.min));
		msg.replace("[maxx]", String(Ais.max));
		msg.replace("[note]", "");
	}
	else {
		if (server.arg(0)==0 || server.arg(1)==0) {
//			msg = SendHTML(server.arg(0), server.arg(1), "please fill in the blank(s)");
			msg.replace("[minn]", server.arg(0));
			msg.replace("[maxx]", server.arg(1));
			msg.replace("[note]", "please fill in the blank(s)");
		}
		else {
//			writeToSpiffs("min", server.arg(0));
//			writeToSpiffs("max", server.arg(1));
//			jsonHandler->writeSdata("min", server.arg(0));
//			jsonHandler->writeSdata("max", server.arg(1));
			spiffsHandler->writeToSpiffs("min", server.arg(0));
			spiffsHandler->writeToSpiffs("max", server.arg(1));
			Ais.min = server.arg(0).toInt();
			Ais.max = server.arg(1).toInt();
//			msg = "Configuration sent. Min=" + server.arg(0) + " Max=" + server.arg(1);
//			msg = SendHTML(server.arg(0), server.arg(1), "Configuration sent.");
			msg.replace("[minn]", server.arg(0));
			msg.replace("[maxx]", server.arg(1));
			msg.replace("[note]", "Saved");
		}
	}
	server.send(200, "text/html", msg);
}
