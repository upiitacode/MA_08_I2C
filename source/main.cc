#include "TM4C123.h"                    // Device header
#include "serial_stream_tm4c.h"
#include "RGBLed.h"

void delay_ms(int delay);

int main(){
	//Iitialize system
	SerialUSART0 serial(9600);
	RGBLed led;
	int myBuffer[20];

	//User application
	led.write(RGB_COLOR_RED);
	serial.printf("Hello, World!\n");
	while(1){
		led.write(serial.getChar());
	}
}
