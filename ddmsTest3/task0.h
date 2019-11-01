/*
 * task0.h
 *
 *  Created on: Mar 25, 2019
 *      Author: annuar
 */

#ifndef TASK0_H_
#define TASK0_H_

#include "Arduino.h"
#include <Wire.h>
#include <driver/adc.h>
#include <SSD1306Spi.h>
#include <OLEDDisplayUi.h>
#include <stdlib.h>

#include "images.h"
#include "board.h"
#include "ais.h"
#include "waktu.h"
#include "wifiHttp.h"

#include "esp_task_wdt.h"

void codeForTask0(void * parameter);
bool DoorClose();
bool MainPower();
void BatteryPower();
float rollAverage(float prev, float newData, float roll);
void enterLine(String s);
void core0Proceed(bool state);
void UiInit();
String twoDigits(int digits);

void setupDisplay(void);
void titleFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void typeA(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void typeB(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void typeC(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);

#endif /* TASK0_H_ */
