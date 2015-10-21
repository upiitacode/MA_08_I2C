#include "TM4C123.h"                    // Device header
#include "serial_stream_tm4c.h"

void delay_ms(int delay);

int main(){
	//Iitialize system
	SerialUSART0 serial(9600);
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
