#ifndef _MPU6050_H
#define _MPU6050_H

#include <stdint.h>
#include "I2CBus.h"

class MPU6050{
	private:
		I2CBus *i2c;
		void writeRegister(unsigned char regAddress,
			unsigned char regValue);
		void deviceConfiguration(void);
	public:
		MPU6050(I2CBus &i2c);
		int16_t readAccel(char axis);
		int16_t readGyro(char axis);
		void readGyroAllAxis(int16_t* gx, int16_t* gy, int16_t* gz);
		void readAccelAllAxis(int16_t* ax, int16_t* ay, int16_t* az);
};

#endif// _MPU6050_H
