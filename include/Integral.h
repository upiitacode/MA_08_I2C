#ifndef _INTEGRAL_H
#define _INTEGRAL_H

class Integral{
	public:
		virtual float getValue(void) = 0;
		virtual void addDeltaX(float delta_x) = 0;
		virtual void resetToInitialCondition(float initial_condition) = 0;
};

#endif// _INTEGRAL_H
