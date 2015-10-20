#ifndef _SERIAL_STREAM_H
#define _SERIAL_STREAM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

class Serial_stream{
	public:
		virtual char getChar(void) = 0;
		virtual void sendChar(char) = 0;
		void puts(const char * pString);
		int gets(char * pBuffer, int bufferSize);
		void printf(const char * format, ...) __attribute__ ((format (printf, 2, 3)));
};

#endif
