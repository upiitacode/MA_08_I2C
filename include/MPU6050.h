#ifndef _MPU6050_H
#define _MPU6050_H

#include <stdint.h>
#include "I2CBus.h"


template <typename T>
class Data3D{
	public:
		T x;
		T y;
		T z;
		Data3D(T x = 0, T y = 0, T z = 0){
			this->x = x;
			this->y = y;
			this->z = z;
		}
};

class MPU6050{
	public:
		static const int ScaleRange250 = 250;
		static const int ScaleRange500 = 500;
		static const int ScaleRange1000 = 1000;
		static const int ScaleRange2000 = 2000;
	private:
		I2CBus *i2c;
		int16_t offset_x;
		int16_t offset_y;
		int16_t offset_z;
		int scaleRange;
		void writeRegister(unsigned char regAddress,
			unsigned char regValue);
		void deviceConfiguration(void);
	public:
		MPU6050(I2CBus &i2c, int scaleRange = ScaleRange1000);
		int16_t readAccel(char axis);
		int16_t readGyro(char axis);
		void readGyroAllAxis(int16_t* gx, int16_t* gy, int16_t* gz);
		void readAccelAllAxis(int16_t* ax, int16_t* ay, int16_t* az);
		Data3D<float> readCompensatedGyro(void);
		void calibrateGyro(void);
};

#endif// _MPU6050_H
