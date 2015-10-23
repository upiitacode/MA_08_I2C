#include "TM4C123.h"                    // Device header
#include "serial_stream_tm4c.h"
#include "RGBLed.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "delay.h"
#include "I2CBus_TM4C.h"
#include "MPU6050.h"

int main(){
	//Iitialize system
	SerialUSART0 serial(9600);
	RGBLed led;
	I2CBus0 i2c;
	MPU6050 mpu(i2c);

	//OS Configuration
	SystemCoreClockUpdate();
	osKernelInitialize();
	osKernelStart();

	//User application
	led.write(RGBLed::COLOR_WHITE);
	serial.printf("CPU speed: %d\n",(int) SystemCoreClock);

	while(1){
		serial.printf("Ax = %d, Ay = %d, Az = %d, Wx = %d, Wy = %d, Wz = %d\n",
			mpu.readAccel('x'),
			mpu.readAccel('y'),
			mpu.readAccel('z'),
			mpu.readGyro('x'),
			mpu.readGyro('y'),
			mpu.readGyro('z'));
		delay_us(500000);
		led.write(RGBLed::COLOR_BLUE);
		delay_us(500000);
		led.write(RGBLed::COLOR_GREEN);
	}
}
