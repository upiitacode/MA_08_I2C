#include "TM4C123.h"                    // Device header
#include "retarget_tm4c.h"
#include "serial_stdio.h"
#include "mpu6050.h"

void delay_ms(int delay);

Serial_t USART0_serial = {UART0_getChar, UART0_sendChar}; 

int main(){
	UART0_init(9600);
	mp6050_init();
	while(1){
		//serial_gets(USART0_serial,myInputBuffer,20);
		serial_printf(USART0_serial,"ax=%6f, ay=%6f, az=%6f\n",
			mp6050_readAccel('x')*(9.8/16384.0),mp6050_readAccel('y')*(9.8/16384.0),mp6050_readAccel('z')*(9.8/16384.0));
			delay_ms(0xFFFFF);
	}
}

void delay_ms(int delay){
	for(int i=0; i<delay; i++){
	}
}
