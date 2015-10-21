#include "RGBLed.h"
#include "TM4C123.h"

const int RGBLed::COLOR_BLACK = (0x00);
const int RGBLed::COLOR_RED = (0x1<<1);
const int RGBLed::COLOR_BLUE = (0x1<<2);
const int RGBLed::COLOR_GREEN = (0x1<<3);
const int RGBLed::COLOR_WHITE = ((0x1<<3)|(0x1<<2)|(0x1<<1)) ;

RGBLed::RGBLed(){
	SYSCTL->RCGCGPIO|=(0x1<<5);//Activamos Periferico GPIOF
	GPIOF->DEN|=(0x1<<1)|(0x1<<2)|(0x1<<3);//GPIO[3:1] as output
	GPIOF->DIR|=(0x1<<1)|(0x1<<2)|(0x1<<3);//GPIO[3:1] as output
}

void RGBLed::write(int color){
	((int *)GPIOF_BASE)[COLOR_WHITE] = color;
}
