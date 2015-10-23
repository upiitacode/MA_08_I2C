#ifndef _SQUARE_INTEGRAL_H
#define _SQUARE_INTEGRAL_H

#include "Integral.h"

class SquareIntegral : public Integral{
	private:
		float x;
		float delta_t;
	public:
		SquareIntegral(float initial_condition, float delta_t = 1);
		virtual float getValue(void);
		virtual void addDeltaX(float delta_x);
		virtual void resetToInitialCondition(float initial_condition);
};

#endif// _SQUARE_INTEGRAL_H
