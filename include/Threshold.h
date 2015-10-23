#ifndef _THRESHOLD_H
#define _THRESHOLD_H

class Threshold{
	public:
		virtual float filter(float signal) = 0;
};

class RangeThreshold : public Threshold{
	float lowerThreshHold;
	float upperThreshold;
	public:
		RangeThreshold(float lowerThreshHold, float upperThreshold);
		virtual float filter(float signal);
};

#endif // _THRESHOLD_H
