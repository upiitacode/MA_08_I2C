


#include "TM4C123.h"                    // Device header
#include "retarget_tm4c.h"
#include "serial_stdio.h"

void delay_ms(int delay);

Serial_t USART0_serial = {UART0_getChar, UART0_sendChar}; 
#define BufferSize 80

int main(){
	char buffer[BufferSize];
	int counter=1;
	UART0_init(9600);
	serial_printf(USART0_serial,"\nIngrese comando\n");
	while(1){
		serial_printf(USART0_serial,"%d$ ",counter++);
		serial_gets(USART0_serial,buffer,BufferSize);
		serial_printf(USART0_serial,"%s\n",buffer);
		delay_ms(0xFFFFF);
	}
}

void delay_ms(int delay){
	for(int i=0; i<delay; i++){

	}
}
