#include "lcd.h"
#include "hd44780_settings.h"
#include "hd44780.h"

void initLCD(void){
	lcd_init();
	lcd_clrscr();
	lcd_home();
}

void greeting(void){
	lcd_puts("  WELCOME HOME! ");
	lcd_goto(0x40);
	lcd_puts("     *CHAPS*    ");
}