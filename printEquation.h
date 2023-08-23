#pragma once
#include "equationParams.h"
#include "doubleOperations.h"
#include <math.h>
#include <stdio.h>

// Uses answers to print out the answers.
void printAnswers(const Answers answers);
// Uses coefficients to print out the equation in the "ax^2 + bx + c" format.
void printFormattedEquation(const Coefficients coefficients);
