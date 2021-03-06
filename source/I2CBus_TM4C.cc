#include "I2CBus_TM4C.h"
#include "TM4C123.h"                    // Device header

I2CBus0::I2CBus0(void){
	SYSCTL->RCGCGPIO|=0x1<<1;//Turn on GPIOB (for I2C0)
	SYSCTL->RCGCI2C|=0x1;//Turn on I2C0

	//configure B2(SCL) and B3(SDA) for I2C signals
	GPIOB->DEN|=(0x1<<2)|(0x1<<3); //digital typ�
	GPIOB->PUR|=(0x1<<2)|(0x1<<3); //pull ups
	GPIOB->ODR|=(0x1<<3); //open-drain output (only on SDA pin)
	GPIOB->AFSEL|=(0x1<<2)|(0x1<<3);//alternate functions
	GPIOB->PCTL|=(0x3<<8)|(0x3<<12);//pins controlled by I2C0

	I2C0->MCR=0x10;//I2C module in master mode
	I2C0->MTPR=0x18;//clock configuration 50MHz to 100KHz(standard speed)
}

void I2CBus0::sendData(unsigned char address_7b,unsigned char data){
	I2C0->MSA=(address_7b<<1)|(0x0);//write to address uC->slave
	I2C0->MDR=data;
	I2C0->MCS=0x7;//single master transmit (STOP START RUN)
	while(isBusy());
}

unsigned char I2CBus0::readData(unsigned char address_7b,unsigned char regAddress){
	I2C0->MSA=(address_7b<<1)|(0x0);//write uC->slave
	I2C0->MDR=regAddress;
	I2C0->MCS=0x3;//single master transmit (START RUN)
	while(isBusy());
	I2C0->MSA=(address_7b<<1)|(0x1);//read uC<-slave
	I2C0->MCS=0x7;//single master receive (STOP START RUN)
	while(isBusy());
	return I2C0->MDR;
}

void I2CBus0::sendPacket(unsigned char  address_7b,unsigned char  *pData,int nData){
	int i;
	if(nData>0){
		I2C0->MSA=(address_7b<<1)|(0x0);//write to address uC->slave
		I2C0->MDR=pData[0];
		I2C0->MCS=(nData>1)?0x3:0x7;//single master transmit (START RUN)/(STOP START RUN)
		while(isBusy());
		for(i=1; i<(nData-1); i++){
			I2C0->MDR=pData[i];
			I2C0->MCS=0x1;//single master transmit (RUN)
			while(isBusy());
		}
		if(nData>1){
			I2C0->MDR=pData[nData-1];
			I2C0->MCS=0x5;//single master transmit (STOP RUN)
			while(isBusy());
		}
	}
}

void I2CBus0::readPacket(unsigned char  address_7b,unsigned char regAddress,
		unsigned char  *pData,int nData){
	if(nData>0){
		//Write register Address
		I2C0->MSA=(address_7b<<1)|(0x0);//write uC->slave
		I2C0->MDR=regAddress;
		I2C0->MCS=0x3;//single master transmit (START RUN)
		while(isBusy());
		//read first byte
		I2C0->MSA=(address_7b<<1)|(0x1);//read uC<-slave
		I2C0->MCS=(nData>1)?0xB:0x7;//single master transmit (ACK START RUN)/(STOP START RUN)
		while(isBusy());
		pData[0] = I2C0->MDR;
		//This only executes if nData >= 3
		for(int i=1; i<(nData-1); i++){
				I2C0->MCS=0x9;//single master transmit (RUN)
				while(isBusy());
				pData[i] = I2C0->MDR;
		}
		// only  executes if nData >= 2
		if(nData>1){
			I2C0->MCS=0x5;//single master transmit (STOP RUN)
			while(isBusy());
			pData[nData-1] = I2C0->MDR;
		}
	}
}

int I2CBus0::isBusy(void){
	return (((I2C0->MCS) & (0x1<<0)) >> 0);//return busy bit
}

