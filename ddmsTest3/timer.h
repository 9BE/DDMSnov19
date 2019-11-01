/*
 * timer.h
 *
 *  Created on: Aug 10, 2018
 *      Author: annuar
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>


class timer {
public:
	timer();
	void test();
	char tock;
	unsigned long tick;

private:
	unsigned long waitUntil;


};

#endif /* TIMER_H_ */
