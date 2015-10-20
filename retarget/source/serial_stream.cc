#include "serial_stream.h"

void Serial_stream::puts(const char * pString){
	char newChar; 
	int i;
	for(i = 0 ; i < 81; i++){
		newChar = pString[i];
		if( newChar != '\0' ){
			this->sendChar(newChar);
		}else{
			break;
		}
	}
}

int Serial_stream::gets(char * pBuffer, int bufferSize){
	char newChar; 
	int i ;
	for(i = 0 ; i < (bufferSize - 1); i++){
		newChar = this->getChar();
		if( (newChar != '\r') ){
			pBuffer[i]=newChar;
		}else{
			pBuffer[i]='\0';
			return i;
		}
	}
	pBuffer[bufferSize-1]='\0';
	return bufferSize-1;
}

#define OUT_BUFFER_SIZE 80

void Serial_stream::printf(const char * format ,...){
	char * tempBuffer;
	va_list args;
	va_start(args, format);
	#if defined ( __GNUC__ )
	vasprintf(&tempBuffer,format, args);
	#else	
	tempBuffer=(char *)malloc(OUT_BUFFER_SIZE);//alocate memory manualy
	vsnprintf(tempBuffer,OUT_BUFFER_SIZE,format,args);
	#endif
	va_end(args);
	this->puts(tempBuffer);
	free(tempBuffer);
}
