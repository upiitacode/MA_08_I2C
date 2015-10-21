#include "delay.h"
#include <stdint.h>

extern uint32_t SystemCoreClock;

void delay_ms(int delay_time){
	int compensatedDelay =  delay_time * (SystemCoreClock / (1000*12));
	for(int i = 0; i < compensatedDelay; i++){
	}
}
