/*
 * all.h
 *
 *  Created on: May 18, 2019
 *      Author: nas
 */

#ifndef WIFIHTTP_H_
#define WIFIHTTP_H_

#include <WiFi.h>
#include <WiFiClient.h>
#include "WiFiGeneric.h"
#include <WebServer.h>
#include "board.h"
#include <Update.h>
#include <WiFiMulti.h>
#include <ESPmDNS.h>
#include "pages.h"
#include "task0.h"
#include "ais.h"
#include "JsonHandler.h"
#include "han.h"

void setupWiFi(void);
void StatusViaWiFi(void);
void StatusViaWiFi(void);
void handleConfDDMS();
//String SendHTML(String minn, String maxx, String note);
bool nine();
void setupServer(void);
bool adTech();

#endif /* WIFIHTTP_H_ */
