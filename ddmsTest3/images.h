/*
 * images.h
 *
 *  Created on: Mar 3, 2019
 *      Author: annuar
 */

#ifndef IMAGES_H_
#define IMAGES_H_

const unsigned char activeSymbol[] PROGMEM = {
    B00000000,
    B00000000,
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B00100100,
    B00011000
};

const unsigned char inactiveSymbol[] PROGMEM = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000
};


#endif /* IMAGES_H_ */
