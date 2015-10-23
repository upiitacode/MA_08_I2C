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

const float threshold_limit = 0.12;
const int sampling_period_ms = 5;
const float delta_t = (sampling_period_ms/1000.0);
const int print_period_ms = 100;

int main(){
	//Initialize system
	SerialUSART0 serial(9600);
	led = new RGBLed;
	I2CBus0 i2c;
	mpu = new MPU6050(i2c,MPU6050::ScaleRange1000);
	mpu->calibrateGyro();

	//User application
	led->write(RGBLed::COLOR_WHITE);
	serial.printf("CPU speed: %d\n",(int) SystemCoreClock);
	
	
	threshold = new RangeThreshold(-threshold_limit,threshold_limit);
	gyroData = new Data3D<float>;
	filteredData = new Data3D<float>;

	integralx = new SquareIntegral(0,delta_t);
	integraly = new SquareIntegral(0,delta_t);
	integralz = new SquareIntegral(0,delta_t);

	//OS Configuration
	SystemCoreClockUpdate();
	osTimerId id1;  
	osKernelInitialize();
	uint32_t exec1 = 1;
  id1 = osTimerCreate (osTimer(Timer1), osTimerPeriodic, &exec1);
	osKernelStart();
	osTimerStart (id1, sampling_period_ms); 

	while(1){
		serial.printf("Tx=%4.1f,Ty=%4.1f,Tz=%4.1f\n",
			integralx->getValue(),
			integraly->getValue(),
			integralz->getValue());
		osDelay(print_period_ms);
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
	filteredData->x = threshold->filter(gyroData->x);
	filteredData->y = threshold->filter(gyroData->y);
	filteredData->z = threshold->filter(gyroData->z);

	integralx->addDeltaX(filteredData->x);
	integraly->addDeltaX(filteredData->y);
	integralz->addDeltaX(filteredData->z);
}
