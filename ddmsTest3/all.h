/*
 * all.h
 *
 *  Created on: May 18, 2019
 *      Author: nas
 */

#ifndef ALL_H_
#define ALL_H_

#include "Arduino.h"
#include "task0.h"
#include "task1.h"
#include "wifiHttp.h"
#include <WebServer.h>
#include "ais.h"
#include "timer.h"
#include "waktu.h"
#include "JsonHandler.h"
#include "SpiffsHandler.h"
#include "esp_task_wdt.h"
#include "han.h"

void SelectPort(byte port);
void hantarAiS();
void connectSonar();
void connectHopper();
void runOnPowered();
void runOnBattery();



#endif /* ALL_H_ */
