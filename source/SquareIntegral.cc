#include "SquareIntegral.h"

SquareIntegral::SquareIntegral(float initial_condition, float delta_t){
	this->x = initial_condition;
	this->delta_t = delta_t;
}

float SquareIntegral::getValue(void){
	return this->x;
}

void SquareIntegral::addDeltaX(float delta_x){
	this->x += this->delta_t * delta_x;
}

void SquareIntegral::resetToInitialCondition(float initial_condition){
	this->x = initial_condition;
}
