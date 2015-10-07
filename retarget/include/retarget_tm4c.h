#ifndef _RETARGET_TM4C_H
#define _RETARGET_TM4C_H
#include "TM4C123.h" 
void UART0_init(int baudrate);
void UART0_sendChar(char c);
char UART0_getChar(void);

void UART3_init(int baudrate);
void UART3_sendChar(char c);
char UART3_getChar(void);

#endif

