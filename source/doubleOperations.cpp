#include "../include/doubleOperations.h"

bool areSameDouble(double f, double s)
{
	return fabs(f - s) < EPSILON; // Works only near zero.
}

bool isGreaterDouble(double f, double s)
{
	return (f - s) > EPSILON; // Works only near zero.
}

bool isLessDouble(double f, double s)
{
	return (f - s) < EPSILON; // Works only near zero.
}