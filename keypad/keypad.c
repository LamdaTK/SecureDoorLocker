#include "keypad.h"
#include "lcd/hd44780.h"

volatile int16_t counter = 320; // assuming a interrupt happens after 30ms with 125kHz of clock frequency,prescaller is 64
volatile int8_t isStarPressed = 0;
int8_t isPolling = 0;
volatile int8_t isHashPressed = 0;
volatile int a=0;volatile int b=0;volatile int c=0;


void initKeyPad() {
    //innitializing keypad pin direction
    KEYPADD = 15;
    //innitializing keypad * function to indicate the start scanning keypad
    
}

void KeypadDisabled() {
	TCCR0&=0xF8;
    isPolling = 0;
}

void KeypadPoll() {
    TCCR0 |= _BV(WGM01) | _BV(CS00);
    OCR0 |= 250;
    TIMSK |= _BV(OCIE0);
    isPolling = 1;
}

static int8_t getKey(int8_t pin) {
    int8_t num = 0;
        switch (pin) {
            case 0x11: {num = '1';//17(0x09) case 15 => changed to suit the case
                break;
				}
            case 0x21: {num = '2'; //33(0x0A) case 14 => changed to suit the case
                break;
				}
            case 0x41: {num = '3'; //65
                break;
				}
            case 0x12: {num = '4'; //18
                break;
				}
            case 0x22: {num = '5'; //34(0x12) case 19 => changed to suit the case
                break;
				}
            case 0x42: {num = '6'; //66
                break;
				}
            case 0x14: {num = '7'; //20 
                break;
				}
            case 0x24: {num = '8'; //36
                break;
				}
            case 0x44: {num = '9'; //68
                break;
				}
            case 0x28: {num = '0'; //40
                break;
				}
			case 0x38: {num='0';		//56, some times the MCU shows this number also some times not, Probably cuz of debounce which couldn't avoid
				break;
				}
            case 0x18: {
				num = '*'; //24
				isStarPressed=1;
                break;
				}
            case 0x48: {
                num = '#'; //72
				isHashPressed = 1;
                break;
				}
			default:{break;}
    }
    return num;
}

int pos=0;

volatile char arr[8];

void driveKeypad(void) {
	
	for(int8_t row=0;row<4;row++){
	
		_delay_ms(20);
	
		KEYPADP = _BV(row);
		
		_delay_ms(20);
		
		int pin=PINB;
		
		_delay_ms(20);
		
		
		if(pin>=17 && (pin!=0x18||pin!=0x48)){
		
			while(PINB>15){}
			
			_delay_ms(20);
		
			int key=getKey(pin)&0xCF;
			
			if(key<=9){

				arr[pos]=(char)(key|0x30);
				arr[pos+1]='\0';
				
				lcd_puts("*");
			
				pos++;
				
				break;
			}		
		}
		
		KEYPADP = 0b00000000;
		
		_delay_ms(5);	
	}
}


ISR(TIMER0_COMP_vect) {
    counter--;	
    if (counter == 0) {
		if(!isHashPressed){
			
			driveKeypad();
		}else{
			KeypadDisabled();
		}
        counter = 320;
    }
}