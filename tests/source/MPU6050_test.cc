#include "gmock/gmock.h"
using ::testing::NiceMock;

#include "MPU6050.h"

class MockI2CBus : public I2CBus{
	public:
		MOCK_METHOD2(sendData, void(unsigned char, unsigned char));
		MOCK_METHOD2(readData, unsigned char(unsigned char, unsigned char));
		MOCK_METHOD3(sendPacket, void(unsigned char, unsigned char*, int));
		MOCK_METHOD4(readPacket, void(unsigned char, unsigned char, unsigned char*, int));
};

TEST(MPU6050Test, ThatNewDeviceCanBeCreated){
	NiceMock<MockI2CBus> i2c;
	MPU6050 mpu(i2c);
}
