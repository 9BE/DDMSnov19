/*
 * SpiffsHandler.cpp
 *
 *  Created on: Jun 24, 2019
 *      Author: suhaimi
 */

#include "SpiffsHandler.h"

SpiffsHandler::SpiffsHandler() {
	// TODO Auto-generated constructor stub

}

SpiffsHandler::~SpiffsHandler() {
	// TODO Auto-generated destructor stub
}

/* function #5 */
String SpiffsHandler::readFromSpiffs(String whatToRead)
{
	bool err = false;
	String res = "";
	if (!SPIFFS.begin(true)) {
		hantu("An Error has occurred while mounting SPIFFS");
		err = true;
	}

	if (!err) {
		File file; // @suppress("Abstract class cannot be instantiated")
		String fileName = "/";
		whatToRead.toLowerCase();
		fileName += whatToRead;
		fileName += ".txt";

		file = SPIFFS.open(fileName);

		if(!file){
			hantu("Failed to open file for reading");
			err = true;
		}

		if (!err) {
			while(file.available()){
				res += file.readString();
			}
			hantu(whatToRead + "::");
			hantu(res);
			file.close();
		}
	}

	return res;
}

/* function #4 */
bool SpiffsHandler::writeToSpiffs(String whatToSave, String value)
{
	bool err = false;
	if (!SPIFFS.begin(true)) {
		err = true;
	}

	if (!err) {
		String fileName = "/";
		whatToSave.toLowerCase();
		fileName += whatToSave;
		fileName += ".txt";
		File file = SPIFFS.open(fileName, FILE_WRITE);

		if (!file) {
			hantu("There was an error opening the file for writing");
			err = true;
		}

		if (!err && file.print(value)) {
			hantu("File was written");

		} else {
			hantu("File write failed");
		}

		file.close();
	}

	return !err;
}

void SpiffsHandler::mulaFiles(bool mulai) {

	SPIFFS.begin();

	String str, tmp;
	File root = SPIFFS.open("/", FILE_READ);
	File dir = root.openNextFile();
	while (dir) {
		str += dir.name();
		str += " / ";
		str += dir.size();
		str += "\r\n";

		if (mulai) {
			tmp = dir.name();
			if (tmp.indexOf("json") > 0 || tmp.indexOf("txt") > 0) {
				str = "Delete - ";
				str += dir.name();
				SPIFFS.remove(dir.name());
			}
		}
		else {
			str = "Exist -";
			str += dir.name();
			str += " / ";
			str += dir.size();
		}
		hantu(str);
		dir = root.openNextFile();

	}

	File configFile;

	if (!SPIFFS.exists("/i.txt")) {

		configFile = SPIFFS.open("/i.txt", "w");
		if (configFile) {
			configFile.print("1");
			configFile.close();
			hantu("Create - /i.txt");
		}
	}

	if (!SPIFFS.exists("/n.txt")) {

		configFile = SPIFFS.open("/n.txt", "w");
		if (configFile) {
			configFile.print("UNKNOWN");
			configFile.close();
			hantu("Create - /n.txt");
		}
	}

	if (!SPIFFS.exists("/j.txt")) {

		configFile = SPIFFS.open("/j.txt", "w");
		if (configFile) {
			configFile.print("d");
			configFile.close();
			hantu("Create - /j.txt");
		}
	}

	if (!SPIFFS.exists("/c.txt")) {

		configFile = SPIFFS.open("/c.txt", "w");
		if (configFile) {
			configFile.print("I4N2IP.png");
			configFile.close();
			hantu("Create - /c.txt");
		}
	}

	if (!SPIFFS.exists("/s.txt")) {

		configFile = SPIFFS.open("/s.txt", "w");
		if (configFile) {
			configFile.print("I4N2IP.png");
			configFile.close();
			hantu("Create - /s.txt");
		}
	}

	if (!SPIFFS.exists("/m.txt")) {

		configFile = SPIFFS.open("/m.txt", "w");
		if (configFile) {
			configFile.print("A00000");
			configFile.close();
			hantu("Create - /m.txt");
		}
	}

	if (!SPIFFS.exists("/e.txt")) {

		configFile = SPIFFS.open("/e.txt", "w");
		if (configFile) {
			configFile.print("10800000");
			configFile.close();
			hantu("Create - /e.txt");
		}
	}

	if (!SPIFFS.exists("/g.txt")) {

		configFile = SPIFFS.open("/g.txt", "w");
		if (configFile) {
			configFile.print("GF7TDK,G1OFJV");
			configFile.close();
			hantu("Create - /g.txt");
		}
	}

	if (!SPIFFS.exists("/sonar.txt")) {

		configFile = SPIFFS.open("/sonar.txt", "w");
		if (configFile) {
			configFile.print("1");
			configFile.close();
			hantu("Create - /sonar.txt");
		}
	}

	if (!SPIFFS.exists("/min.txt")) {

		configFile = SPIFFS.open("/min.txt", "w");
		if (configFile) {
			configFile.print("500");
			configFile.close();
			hantu("Create - /min.txt");
		}
	}

	if (!SPIFFS.exists("/max.txt")) {

		configFile = SPIFFS.open("/max.txt", "w");
		if (configFile) {
			configFile.print("5000");
			configFile.close();
			hantu("Create - /max.txt");
		}
	}

	if (!SPIFFS.exists("/hopper.txt")) {

		configFile = SPIFFS.open("/hopper.txt", "w");
		if (configFile) {
			configFile.print("0");
			configFile.close();
			hantu("Create - /hopper.txt");
		}
	}

	SPIFFS.end();

}

void SpiffsHandler::mulaFiles() {

	SPIFFS.begin();

	String str, tmp;
	File root = SPIFFS.open("/", FILE_READ);
	File dir = root.openNextFile();
	while (dir) {
		str += dir.name();
		str += " / ";
		str += dir.size();
		str += "\r\n";

		if (freshSetup) {
			tmp = dir.name();
			if (tmp.indexOf("json") > 0 || tmp.indexOf("txt") > 0) {
				str = "Delete - ";
				str += dir.name();
				SPIFFS.remove(dir.name());
			}
		}
		else {
			str = "Exist -";
			str += dir.name();
			str += " / ";
			str += dir.size();
		}
		hantu(str);
		dir = root.openNextFile();

	}

	File configFile;

	if (!SPIFFS.exists("/i.txt")) {

		configFile = SPIFFS.open("/i.txt", "w");
		if (configFile) {
			configFile.print("1");
			configFile.close();
			hantu("Create - /i.txt");
		}
	}

	if (!SPIFFS.exists("/n.txt")) {

		configFile = SPIFFS.open("/n.txt", "w");
		if (configFile) {
			configFile.print("UNKNOWN");
			configFile.close();
			hantu("Create - /n.txt");
		}
	}

	if (!SPIFFS.exists("/j.txt")) {

		configFile = SPIFFS.open("/j.txt", "w");
		if (configFile) {
			configFile.print("d");
			configFile.close();
			hantu("Create - /j.txt");
		}
	}

	if (!SPIFFS.exists("/c.txt")) {

		configFile = SPIFFS.open("/c.txt", "w");
		if (configFile) {
			configFile.print("I4N2IP.png");
			configFile.close();
			hantu("Create - /c.txt");
		}
	}

	if (!SPIFFS.exists("/s.txt")) {

		configFile = SPIFFS.open("/s.txt", "w");
		if (configFile) {
			configFile.print("I4N2IP.png");
			configFile.close();
			hantu("Create - /s.txt");
		}
	}

	if (!SPIFFS.exists("/m.txt")) {

		configFile = SPIFFS.open("/m.txt", "w");
		if (configFile) {
			configFile.print("A00000");
			configFile.close();
			hantu("Create - /m.txt");
		}
	}

	if (!SPIFFS.exists("/e.txt")) {

		configFile = SPIFFS.open("/e.txt", "w");
		if (configFile) {
			configFile.print("10800000");
			configFile.close();
			hantu("Create - /e.txt");
		}
	}

	if (!SPIFFS.exists("/g.txt")) {

		configFile = SPIFFS.open("/g.txt", "w");
		if (configFile) {
			configFile.print("GF7TDK,G1OFJV");
			configFile.close();
			hantu("Create - /g.txt");
		}
	}

	if (!SPIFFS.exists("/sonar.txt")) {

		configFile = SPIFFS.open("/sonar.txt", "w");
		if (configFile) {
			configFile.print("1");
			configFile.close();
			hantu("Create - /sonar.txt");
		}
	}

	if (!SPIFFS.exists("/min.txt")) {

		configFile = SPIFFS.open("/min.txt", "w");
		if (configFile) {
			configFile.print("500");
			configFile.close();
			hantu("Create - /min.txt");
		}
	}

	if (!SPIFFS.exists("/max.txt")) {

		configFile = SPIFFS.open("/max.txt", "w");
		if (configFile) {
			configFile.print("5000");
			configFile.close();
			hantu("Create - /max.txt");
		}
	}

	if (!SPIFFS.exists("/hopper.txt")) {

		configFile = SPIFFS.open("/hopper.txt", "w");
		if (configFile) {
			configFile.print("0");
			configFile.close();
			hantu("Create - /hopper.txt");
		}
	}

	SPIFFS.end();

}

