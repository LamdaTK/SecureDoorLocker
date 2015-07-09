#include "eeprom.h"

/*
* initial method to write to eeprom
* without using eeprom interrupts
*/
void writeEEPROM(unsigned int uiAddress, unsigned char ucData){
	
	while(EECR & (1<<EEWE));	/* Wait for completion of previous write */
		
	EEAR = uiAddress;			/* Set up address and data registers */
	
	EEDR = ucData;
	
	
	EECR |= (1<<EEMWE);		/* Write logical one to EEMWE */
	
	EECR |= (1<<EEWE);			/* Start eeprom write by setting EEWE */
}

unsigned char readEEPROM(unsigned int uiAddress){
	
	while(EECR & (1<<EEWE));	/* Wait for completion of previous write */
	
	EEAR = uiAddress;			/* Set up address register */
	
	EECR |= (1<<EERE);			/* Start eeprom read by writing EERE */
	
	return EEDR;				/* Return data from data register */
}

uint8_t num1=0;uint8_t num2=0;uint8_t num3=0;

void processNumber(long a){
	num1=(a/65025);
	num2=((a%65025)/255);
	num3=((a%65025)%255);
}

unsigned char savePassword(long g){
	if(g>0){
		processNumber(g);
		unsigned char ca=getFCell();
		
		writeEEPROM(ca,num1);
		writeEEPROM((ca+1),num2);
		writeEEPROM((ca+2),num3);
	}
	return 1;
}

unsigned char validatePassword(long f){
	if(f>0){
		processNumber(f);
		for(int i=0;i<1024;i++){
			if(i%3==0){
				unsigned char a=readEEPROM(i);
				if(a==num1){
					unsigned char b=readEEPROM((i+1));
					if(b==num2){
						unsigned char c=readEEPROM((i+2));
						if(c==num3){
							return 1;
						}
					}
				}
			}
			i+=3;
		}
	}
	return 0;
}

unsigned char getFCell(void){
	for(int i=0;i<1024;i++){
		if((i%3)==0){
			unsigned char a=readEEPROM(i);
			if(a==0){
				unsigned char b=readEEPROM((i+1));
				if(b==0){
					unsigned char c=readEEPROM((i+2));
					if(c==0){
						return i;
					}
				}
			}
		}
		i+=3;
	}
	return 0;
}

unsigned char deletePassword(long number){
	if(number>0){
		processNumber(number);
		for(int i=0;i<1024;i++){
			if(i%3==0){
				unsigned char a=readEEPROM(i);
				if(a==num1){
					unsigned char b=readEEPROM((i+1));
					if(b==num2){
						unsigned char c=readEEPROM((i+2));
						if(c==num3){
							writeEEPROM(i,0);
							writeEEPROM((i+1),0);
							writeEEPROM((i+2),0);
							return 1;
						}
					}
				}
			}
			i+=3;
		}
	}
	return 0;
}

void clearAll(void){
	for(int i=0;i<1024;i++){
		writeEEPROM(i,0);
	}
}