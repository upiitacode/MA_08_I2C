#include "RGBLed.h"
#include "TM4C123.h"

RGBLed::RGBLed(){
	SYSCTL->RCGCGPIO|=(0x1<<5);//Activamos Periferico GPIOF
	GPIOF->DEN|=(0x1<<1)|(0x1<<2)|(0x1<<3);//GPIO[3:1] as output
	GPIOF->DIR|=(0x1<<1)|(0x1<<2)|(0x1<<3);//GPIO[3:1] as output
}

void RGBLed::write(int color){
	((int *)GPIOF_BASE)[RGB_COLOR_WHITE] = color;
}
