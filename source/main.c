#include "TM4C123.h"                    // Device header
#include "retarget_tm4c.h"
#include "serial_stdio.h"
#include "mpu6050.h"

void delay_ms(int delay);

void rgb_init(void){
	SYSCTL->RCGCGPIO|=(0x1<<5);//Activamos Periferico GPIOF
	GPIOF->DEN|=(0x1<<1)|(0x1<<2)|(0x1<<3);//GPIO[3:1] as output
	GPIOF->DIR|=(0x1<<1)|(0x1<<2)|(0x1<<3);//GPIO[3:1] as output
}

#define RGB_COLOR_RED (0x1<<1)
#define RGB_COLOR_GREEN (0x1<<3)
#define RGB_COLOR_BLUE (0x1<<2)
#define RGB_COLOR_WHITE (RGB_COLOR_RED | RGB_COLOR_GREEN | RGB_COLOR_BLUE)
#define RGB_COLOR_BLACK (0x00)
void rgb_write(int color){
	((int *)GPIOF_BASE)[RGB_COLOR_WHITE] = color;
}

Serial_t USART0_serial = {UART0_getChar, UART0_sendChar}; 

int main(){
	UART0_init(9600);
	mp6050_init();
	rgb_init();
	rgb_write(RGB_COLOR_BLACK);
	SystemCoreClockUpdate();
	SysTick_Config(2500000);//desbordarse cada t=(f/c)=(50*10^6)/(2.5*10^6)= 0.05s 
	
	int16_t gx, gy, gz;
	int16_t ax, ay, az;
	while(1){
		mpu6050_readGyroAllAxis(&gx, &gy, &gz);
		mpu6050_readAccelAllAxis(&ax, &ay, &az);
		serial_printf(USART0_serial,"ax=%d, ay=%d, Az=%6d\n",ax,ay,az);
		//serial_printf(USART0_serial,"gx=%d, gy=%d, gz=%6d\n",gx,gy,gz);
		delay_ms(0xFFFFF);
	}
}

void delay_ms(int delay){
	for(int i=0; i<delay; i++){
	}
}

//rutina de interrupcion
void SysTick_Handler(void){
	static int last_val = 0;
	if (last_val){
		rgb_write(RGB_COLOR_BLACK);
		last_val = 0;
	}else{
		rgb_write(RGB_COLOR_WHITE);
		last_val = 1;
	}
}
