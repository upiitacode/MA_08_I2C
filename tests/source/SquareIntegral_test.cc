#include "gmock/gmock.h"
using ::testing::Eq;
using ::testing::FloatEq;

#include "SquareIntegral.h"

TEST(SquareIntegralTest, OnCreationReturnsIntialCondition){
	float const initial_condition = 5.5;
	SquareIntegral integral(initial_condition);
	EXPECT_THAT(integral.getValue(), FloatEq(initial_condition));
}


TEST(SquareIntegralTest, WhenDeltaTIsOneTheIngtralIsTheSumOfDeltaX){
	float const initial_condition = 4.5;
	float const delta_t = 1.0;
	SquareIntegral integral(initial_condition, delta_t);
	integral.addDeltaX(1.0);	
	integral.addDeltaX(2.0);	
	integral.addDeltaX(3.0);	
	EXPECT_THAT(integral.getValue(), FloatEq(10.5));
}

TEST(SquareIntegralTest, WhenDeltaTIsScaledIingralIsScaled){
	float const initial_condition = 0.0;
	float const scale = 0.1;
	float const delta_t = 1.0;
	float const scaled_delta = delta_t*scale;
	SquareIntegral normalIntegral(initial_condition, delta_t);
	SquareIntegral scaledIntegral(initial_condition,scaled_delta);

	scaledIntegral.addDeltaX(3.4);
	normalIntegral.addDeltaX(3.4);

	EXPECT_THAT(scaledIntegral.getValue(), 
			FloatEq(normalIntegral.getValue()*scale));
}

TEST(SquareIntegralTest, IntegralValueCanBeResetToSomeInitialCondition){
	float const initial_condition = 4.5;
	float const postInitialCondition = -0.3;
	float const delta_t = 1.0;
	SquareIntegral integral(initial_condition, delta_t);
	integral.addDeltaX(1.0);	
	integral.addDeltaX(2.0);	
	integral.addDeltaX(3.0);	
	integral.resetToInitialCondition(postInitialCondition);
	EXPECT_THAT(integral.getValue(), FloatEq(postInitialCondition));
}
