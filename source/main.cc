#include "TM4C123.h"                    // Device header
#include "serial_stream_tm4c.h"

void delay_ms(int delay);

void rgb_init(void){
	SYSCTL->RCGCGPIO|=(0x1<<5);//Activamos Periferico GPIOF
	GPIOF->DEN|=(0x1<<1)|(0x1<<2)|(0x1<<3);//GPIO[3:1] as output
	GPIOF->DIR|=(0x1<<1)|(0x1<<2)|(0x1<<3);//GPIO[3:1] as output
}

#define RGB_COLOR_RED (0x1<<1)
#define RGB_COLOR_GREEN (0x1<<3)
#define RGB_COLOR_BLUE (0x1<<2)
#define RGB_COLOR_WHITE (RGB_COLOR_RED | RGB_COLOR_GREEN | RGB_COLOR_BLUE)
#define RGB_COLOR_BLACK (0x00)
void rgb_write(int color){
	((int *)GPIOF_BASE)[RGB_COLOR_WHITE] = color;
}

int main(){
	//Iitialize system
	SerialUSART0 serial(9600);
	rgb_init();
	//User application
	serial.printf("Hello, World!\n");
	while(1){
		delay_ms(0xFFFF);
	}
}

void delay_ms(int delay){
	for(int i=0; i<delay; i++){
	}
}

extern "C"{
void SysTick_Handler(void){
	static int last_val = 0;
	if (last_val){
		rgb_write(RGB_COLOR_BLACK);
		last_val = 0;
	}else{
		rgb_write(RGB_COLOR_WHITE);
		last_val = 1;
	}
}
}
