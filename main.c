#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//header files for configuring keypad and the system
#include "keypad/keypad.h"
#include "lock/lock.h"
#include "eeprom/eeprom.h"
#include "lcd/lcd.h"

#define MASTER 2567

int main(void){

	start:

	initLocker();
	
	initLCD();
	
	initKeyPad();
	
	sei();
	
	greeting();
	
	//clearAll();
	
	long int key=0;
	
	while(1){
		
		ask:
		KEYPADP=_BV(3);
		
		_delay_us(50);
		
		
		
		if(PINB==24){
			lcd_clrscr();
			lcd_goto(0);
			lcd_puts("Write Your Passs");
			lcd_goto(0x46);
			
			KEYPADP=0b00000000;
			
			_delay_ms(20);
			
			pos=0;
			
			KeypadPoll();
			
			while(!isHashPressed){}
			
		
		}if(isHashPressed){
			
				KEYPADP=0b00000000;
				
				//scan the array and construct the number from it. it could be variable length MAX_LEN=8
				
				_delay_ms(20);
				
				sscanf(arr,"%ld",&key);
				
				if(key==MASTER){
					key=0;
					KEYPADP=0b00000000;
					
					for(int i=0;i<7;i++){lcd_command(_BV(LCD_MOVE)|_BV(LCD_MOVE_DISP)|_BV(LCD_MOVE_RIGHT));_delay_ms(62);}
					lcd_clrscr();
					lcd_home();
					lcd_puts("Welcome to Admin");
					lcd_goto(0x40);
					lcd_puts("1)Insert 2)Delet");
					
					KEYPADP=_BV(0);
					
					while(PINB<15){}
					
					//this is to deal with the key debouncing event.
					_delay_ms(50);
					
					int pinx=PINB;
					
					//key reading after debouncing ends.
					_delay_ms(50);
					
					for(int i=0;i<7;i++){lcd_command(_BV(LCD_MOVE)|_BV(LCD_MOVE_DISP)|_BV(LCD_MOVE_RIGHT));_delay_ms(62);}
					lcd_clrscr();
					lcd_home();
					lcd_puts("Write your PWD!");
					lcd_goto(0x46);
					
					//Poling keypad starts
					KEYPADP=0b00000000;
					
					_delay_ms(20);
					
					pos=0;
					
					KeypadPoll();
					
					while(!isHashPressed){}
					
					if(isHashPressed){
					
						KEYPADP=0b00000000;
				
						sscanf(arr,"%ld",&key);
				
						pos=0;
						
						isHashPressed=0;
					}
					//poling keypad ends
					if(pinx==17){
						for(int i=0;i<7;i++){lcd_command(_BV(LCD_MOVE)|_BV(LCD_MOVE_DISP)|_BV(LCD_MOVE_RIGHT));_delay_ms(62);}
						
						savePassword(key);
						
						key=0;
						
						lcd_clrscr();
						lcd_home();
						lcd_puts(" Password Saved ");
						
						_delay_ms(1500);
						
					}else if(pinx==33){
						
						for(int i=0;i<7;i++){lcd_command(_BV(LCD_MOVE)|_BV(LCD_MOVE_DISP)|_BV(LCD_MOVE_RIGHT));_delay_ms(62);}
						
						deletePassword(key);
						
						key=0;
						
						lcd_clrscr();
						lcd_home();
						lcd_puts("Password Deleted");
						
						_delay_ms(1500);
						
					}
					goto start;
					
				}else if(validatePassword(key)){
					for(int i=0;i<7;i++){lcd_command(_BV(LCD_MOVE)|_BV(LCD_MOVE_DISP)|_BV(LCD_MOVE_RIGHT));_delay_ms(62);}
					lcd_clrscr();
					lcd_home();
					lcd_puts(" Access Granted ");
					open();
					close();
					key=0;
					goto start;
				
				}else{
					for(int i=0;i<7;i++){lcd_command(_BV(LCD_MOVE)|_BV(LCD_MOVE_DISP)|_BV(LCD_MOVE_RIGHT));_delay_ms(62);}
					lcd_clrscr();
					lcd_home();
					lcd_puts("Opz,sorry pal :(");
					lcd_goto(0x40);
					lcd_puts("Lets do it Again");
					
					_delay_ms(1500);
					goto ask;
				}
		
				pos=0;
				
				isHashPressed=0;
		}
	}
	return 0;
}