#ifndef _SERIAL_STREAM_TM4C_H
#define _SERIAL_STREAM_TM4C_H

#include "serial_stream.h"

class SerialUSART0: public Serial_stream{
	public:
		SerialUSART0(int baudrate);
		virtual char getChar(void);
		virtual void sendChar(char c);
};

class SerialUSART3 : public Serial_stream{
	public:
		SerialUSART3(int baudrate);
		virtual char getChar(void);
		virtual void sendChar(char c);
};

#endif // _SERIAL_STREAM_TM4C_H
