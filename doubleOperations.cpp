#include "doubleOperations.h"

bool areSameDouble(double f, double s)
{
	return fabs(f - s) < EPSILON;
}
