#include "Threshold.h"

RangeThreshold::RangeThreshold(float lowerThreshHold, float upperThreshold){
	this->lowerThreshHold = lowerThreshHold;
	this->upperThreshold = upperThreshold;
}

float RangeThreshold::filter(float signal){
	if((signal < lowerThreshHold) || (signal > upperThreshold)){
		return signal;
	}
	else{
		return 0;
	}
}
