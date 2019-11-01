/*
 * task1.h
 *
 *  Created on: Mar 25, 2019
 *      Author: annuar
 */

#ifndef TASK1_H_
#define TASK1_H_

#include "Arduino.h"
#include "ais.h"
#include "waktu.h"
#include "esp_task_wdt.h"
#include "han.h"


void codeForTask1(void * parameter);
int getSmallestValidNumber(int a, int b);
bool IntrestInfo(String test);
void ReadSerial(void);
double toDegree(String snum);


#endif /* TASK1_H_ */
