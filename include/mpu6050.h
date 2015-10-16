#include <stdint.h>

#ifndef _MPU6050_H
#define _MPU6050_H

#define MPU6050_ADDRESS 0x68

#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E
#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40

#define MPU6050_GYRO_XOUT_H 0x43
#define MPU6050_GYRO_XOUT_L 0x44
#define MPU6050_GYRO_YOUT_H 0x45
#define MPU6050_GYRO_YOUT_L 0x46
#define MPU6050_GYRO_ZOUT_H 0x37
#define MPU6050_GYRO_ZOUT_L 0x48

void mp6050_init(void);
int16_t mp6050_readAccel(char axis);
int16_t mp6050_readGyro(char axis);
void mpu6050_readGyroAllAxis(int16_t* gx, int16_t* gy, int16_t* gz);
void mpu6050_readAccelAllAxis(int16_t* ax, int16_t* ay, int16_t* az);

#endif /*_MPU6050_H*/
