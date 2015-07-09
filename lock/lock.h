#ifndef	LOCK_H
#define LOCK_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd/hd44780_settings.h"
#include "lcd/hd44780.h"

#define LOCKERD DDRA
#define openreg 18
#define closereg 9

extern volatile int8_t isOpened;

extern void initLocker(void);
extern void open(void);
extern void close(void);
#endif