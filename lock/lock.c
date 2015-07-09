#include "lock.h"

volatile int8_t isOpened=0;

void initLocker(void){
	DDRD|=_BV(4);
	PORTD|=_BV(4);

	LOCKERD=0xFF;
	MCUCR|=_BV(ISC11);
	GICR|=_BV(INT1);
	
}

void open(void){
	if(!isOpened){
		PORTA=openreg;
		_delay_ms(3000);
		PORTA=0;
		_delay_ms(50);
		isOpened=1;
	}
}

void close(void){
	if(!isOpened){
		PORTA=closereg;
		_delay_ms(1500);
		PORTA=0;
		_delay_ms(50);
		isOpened=0;
		
		lcd_clrscr();
		lcd_home();
		lcd_puts("  Take Care ;)  ");
		lcd_goto(0x40);
		lcd_puts("   Come Soon!   ");
	}
}

ISR(INT1_vect){
	if(!isOpened){
		open();
	}else{
		close();
	}
}