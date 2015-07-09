#ifndef KEYPAD_H
#define KEYPAD_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

//define PIN for keypad
#define KEYPADD DDRB
#define KEYPADP PORTB

extern int8_t isPolling;
extern volatile char arr[8];
extern int pos;
extern volatile int8_t isHashPressed;
extern volatile int8_t isStarPressed;

extern void initKeyPad(void);
extern void KeypadDisabled(void);
extern void KeypadPoll(void);
extern void driveKeypad(void);

#endif