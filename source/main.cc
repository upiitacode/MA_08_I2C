#include "TM4C123.h"                    // Device header
#include "serial_stream_tm4c.h"
#include "RGBLed.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "delay.h"

int main(){
	//Iitialize system
	SerialUSART0 serial(9600);
	RGBLed led;
	SystemCoreClockUpdate();
	osKernelInitialize();
	osKernelStart();
	//User application
	led.write(RGBLed::COLOR_WHITE);
	serial.printf("CPU speed: %d\n",(int) SystemCoreClock);
	while(1){
		delay_us(500000);
		led.write(RGBLed::COLOR_BLUE);
		delay_us(500000);
		led.write(RGBLed::COLOR_GREEN);
	}
}
