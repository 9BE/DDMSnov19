/*
 * timer.cpp
 *
 *  Created on: Aug 10, 2018
 *      Author: annuar
 */

#include "timer.h"

timer::timer()
{
	waitUntil = 0;
	tock = 0;
	tick = 0;
}

void timer::test()
{
	if ((unsigned long)(millis() - waitUntil) >= tick) {  // check for rollover
		tock = 1;
		waitUntil = waitUntil + tick;
	}


}
