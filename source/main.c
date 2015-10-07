#include "TM4C123.h"                    // Device header
#include "retarget_tm4c.h"
#include "serial_stdio.h"
#include "mpu6050.h"

void delay_ms(int delay);

Serial_t USART0_serial = {UART0_getChar, UART0_sendChar}; 

int main(){
	UART0_init(115200);
	mp6050_init();
	serial_printf(USART0_serial,"\nIngrese comando\n");
	while(1){
		serial_printf(USART0_serial,"accel_x=%6d\n",mp6050_readAccel('x'));
		serial_printf(USART0_serial,"accel_y=%6d\n",mp6050_readAccel('y'));
		serial_printf(USART0_serial,"accel_z=%6d\n\n",mp6050_readAccel('z'));
		serial_printf(USART0_serial,"gyro_x=%6d\n",mp6050_readGyro('x'));
		serial_printf(USART0_serial,"gyro_y=%6d\n",mp6050_readGyro('y'));
		serial_printf(USART0_serial,"gyro_z=%6d\n\n",mp6050_readGyro('z'));
		delay_ms(0x2FFFFF);
	}
}

void delay_ms(int delay){
	for(int i=0; i<delay; i++){
	}
}
