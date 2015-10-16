#include "i2c_lib.h"
#include "mpu6050.h"

void mp6050_init(void){
	unsigned char confpacket[] = {0x6B,0x00};
	i2c_config();
	i2c_sendPacket(MPU6050_ADDRESS,confpacket,2);
}

int16_t mp6050_readAccel(char axis){
	int16_t accel_reading = 0;
	unsigned char axis_data_h;
	unsigned char axis_data_l;
	unsigned char axis_address_h;
	
	if((axis >= 'x') && (axis <= 'z')){
		axis_address_h = MPU6050_ACCEL_XOUT_H + (axis - 'x')*2; 
		axis_data_h = i2c_readData(MPU6050_ADDRESS,axis_address_h);
		axis_data_l = i2c_readData(MPU6050_ADDRESS,axis_address_h+1);
		accel_reading = (axis_data_h << 8) | (axis_data_l);
	}
 	return accel_reading;
}

int16_t mp6050_readGyro(char axis){
	int16_t gyro_reading = 0;
	unsigned char axis_data_h;
	unsigned char axis_data_l;
	unsigned char axis_address_h;
	
	if((axis >= 'x') && (axis <= 'z')){
		axis_address_h = MPU6050_GYRO_XOUT_H + (axis - 'x')*2; 
		axis_data_h = i2c_readData(MPU6050_ADDRESS,axis_address_h);
		axis_data_l = i2c_readData(MPU6050_ADDRESS,axis_address_h+1);
		gyro_reading = (axis_data_h << 8) | (axis_data_l);
	}
 	return gyro_reading;
}

void mpu6050_readAccelAllAxis(int16_t* ax, int16_t* ay, int16_t* az){
	unsigned char accel_data[6];
	i2c_readPacket(MPU6050_ADDRESS,MPU6050_ACCEL_XOUT_H,accel_data,6);
	*ax = (accel_data[0] << 8) | (accel_data[1]);
	*ay = (accel_data[2] << 8) | (accel_data[3]);
	*az = (accel_data[4] << 8) | (accel_data[5]);
}

void mpu6050_readGyroAllAxis(int16_t* gx, int16_t* gy, int16_t* gz){
	unsigned char gyro_data[6];
	i2c_readPacket(MPU6050_ADDRESS,MPU6050_GYRO_XOUT_H,gyro_data,6);
	*gx = (gyro_data[0] << 8) | (gyro_data[1]);
	*gy = (gyro_data[2] << 8) | (gyro_data[3]);
	*gz = (gyro_data[4] << 8) | (gyro_data[5]);
}
