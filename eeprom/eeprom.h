#ifndef EEPROM_H
#define EEPROM_H

#include <avr/io.h>
#include <util/delay.h>

extern unsigned char readEEPROM(unsigned int uiAddress);
extern void writeEEPROM(unsigned int uiAddress, unsigned char ucData);

/*
*	this method process the number which is fractions of 255
*	first fractions of 65025
*	then mod 65025 divide by 255
*	finally mod 65025 and mod 255
*
*/
extern void processNumber(long a);

extern unsigned char validatePassword(long b);

extern unsigned char savePassword(long g);

/*
*	method for get the next cell which is divisable by 3;
*	this return the address which is smaller than 1023
*	
*/
extern unsigned char getFCell(void); 

extern unsigned char deletePassword(long a);

extern void clearAll(void);

#endif