#include "TM4C123.h"                    // Device header
#include "serial_stream_tm4c.h"
#include "RGBLed.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "delay.h"
#include "I2CBus_TM4C.h"
#include "MPU6050.h"
#include "SquareIntegral.h"
#include "Threshold.h"

void Timer1_Callback  (void const *arg); 
osTimerDef (Timer1, Timer1_Callback);

RGBLed* led;
MPU6050* mpu;
RangeThreshold* threshold;
Data3D<float>* gyroData;
SquareIntegral* integralx;
SquareIntegral* integraly;
SquareIntegral* integralz;
Data3D<float>* filteredData;

int main(){
	//Initialize system
	SerialUSART0 serial(38400);
	led = new RGBLed;
	I2CBus0 i2c;
	mpu = new MPU6050(i2c);
	mpu->calibrateGyro();

	//User application
	led->write(RGBLed::COLOR_WHITE);
	serial.printf("CPU speed: %d\n",(int) SystemCoreClock);

	threshold = new RangeThreshold(-4.0,4.0);
	gyroData = new Data3D<float>;
	filteredData = new Data3D<float>;

	integralx = new SquareIntegral(0,0.005);
	integraly = new SquareIntegral(0,0.005);
	integralz = new SquareIntegral(0,0.005);

	//OS Configuration
	SystemCoreClockUpdate();
	osTimerId id1;  
	osKernelInitialize();
	uint32_t exec1 = 1;
  id1 = osTimerCreate (osTimer(Timer1), osTimerPeriodic, &exec1);
	osKernelStart();
	osTimerStart (id1, 5); 

	while(1){
		serial.printf("Tx=%4.1f,Ty=%4.1f,Tz=%4.1f\n",
				integralx->getValue(),
				integraly->getValue(),
				integralz->getValue());
		osDelay(100);
	}
}

int lastOutput = 0;

void Timer1_Callback  (void const *arg){
	if(lastOutput == 1){
		lastOutput = 0;
		led->write(RGBLed::COLOR_BLUE);
	}else{
		lastOutput = 1;
		led->write(RGBLed::COLOR_RED);
	}
	*gyroData = mpu->readCompensatedGyro();
	filteredData->x = (2000.0/65535.0) * threshold->filter(gyroData->x);
	filteredData->y = (2000.0/65535.0) * threshold->filter(gyroData->y);
	filteredData->z = (2000.0/65535.0) * threshold->filter(gyroData->z);

	integralx->addDeltaX(filteredData->x);
	integraly->addDeltaX(filteredData->y);
	integralz->addDeltaX(filteredData->z);
}
