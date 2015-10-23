#include "TM4C123.h"                    // Device header
#include "serial_stream_tm4c.h"
#include "RGBLed.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "delay.h"
#include "I2CBus_TM4C.h"
#include "MPU6050.h"
#include "SquareIntegral.h"
#include "Threshold.h"

int main(){
	//Iitialize system
	SerialUSART0 serial(9600);
	RGBLed led;
	I2CBus0 i2c;
	MPU6050 mpu(i2c);
	mpu.calibrateGyro();

	//User application
	led.write(RGBLed::COLOR_WHITE);
	serial.printf("CPU speed: %d\n",(int) SystemCoreClock);

	RangeThreshold threshold(-5,5);
	Data3D<float> gyroData;
	Data3D<float> filteredData;

	SquareIntegral integralx(0,0.1);
	SquareIntegral integraly(0,0.1);
	SquareIntegral integralz(0,0.1);

	//OS Configuration
	SystemCoreClockUpdate();
	osKernelInitialize();
	osKernelStart();

	while(1){
		gyroData = mpu.readCompensatedGyro();
		filteredData.x = threshold.filter(gyroData.x);
		filteredData.y = threshold.filter(gyroData.y);
		filteredData.z = threshold.filter(gyroData.z);

		integralx.addDeltaX(filteredData.x);
		integraly.addDeltaX(filteredData.y);
		integralz.addDeltaX(filteredData.z);

		serial.printf("Wx=%4.1f,Wy=%4.1f,Wz=%4.1f,Tx=%4.1f,Ty=%4.1f,Tz=%4.1f\n",
				filteredData.x,
				filteredData.y,
				filteredData.z,
				integralx.getValue(),
				integraly.getValue(),
				integralz.getValue());
		delay_ms(100);
	}
}
