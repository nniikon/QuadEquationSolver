#pragma once
#include "solveEquation.h"
#include "inputCoefficients.h"
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>


struct SolveTestData
{
    Coefficients coefficients;
    Answers answers;
    const char* name;
};

// Test solve.cpp.
void testSolve();

// Test inputCoefficients.cpp.
void testEquationInput();

// Amount of solve tests.
const int nSolveTests = 8;

extern SolveTestData solveTestData[nSolveTests];
