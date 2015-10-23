#ifndef _I2CBUS_TM4C_H
#define _I2CBUS_TM4C_H

#include "I2CBus.h"

class I2CBus0 : public I2CBus{
	private:
		int isBusy(void);
	public:
		I2CBus0(void);
		virtual void sendData(unsigned char  address_7b, unsigned char data);
		virtual unsigned char readData(unsigned char address_7b, unsigned char regAddress);
		virtual void sendPacket(unsigned char  address_7b, unsigned char  *pData, int nData);
		virtual void readPacket(unsigned char  address_7b, unsigned char regAddress, unsigned char *pData, int nData);
};

#endif// _I2CBUS_TM4C_H
