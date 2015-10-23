#include "gmock/gmock.h"
using ::testing::FloatEq;

#include "Threshold.h"

TEST(ThresholdTest,ThatSignalIsInRageItGoesOutTheSame){
	const float lower_limit = -1.0;
	const float upper_limit = 1.0;
	Threshold* threshold = new RangeThreshold(lower_limit, upper_limit);

	float value_out_of_upper_range = 4;
	float value_out_of_lower_range = -1.2;

	EXPECT_THAT(threshold->filter(value_out_of_upper_range), FloatEq(value_out_of_upper_range));
	EXPECT_THAT(threshold->filter(value_out_of_lower_range), FloatEq(value_out_of_lower_range));
}

TEST(ThresholdTest,ThatSignalIsSetToZeroWhenInsideRange){
	const float lower_limit = -1.0;
	const float upper_limit = 1.0;
	Threshold* threshold = new RangeThreshold(lower_limit, upper_limit);

	float value_in_range_1 = 0.9;
	float value_in_range_2 = -0.9;

	EXPECT_THAT(threshold->filter(value_in_range_1), FloatEq(0));
	EXPECT_THAT(threshold->filter(value_in_range_2), FloatEq(0));
}

