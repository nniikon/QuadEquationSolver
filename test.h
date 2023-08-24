/**
 * @file test.h
 * @brief This file defines a test suite for the equation solver and coefficient input functions.
 */

#pragma once
#include "solveEquation.h"
#include "inputCoefficients.h"
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Structure to hold test data for solving equations.
 */
struct SolveTestData {
    Coefficients coefficients; /**< Coefficients for the equation */
    Answers answers;           /**< Expected answers for the equation */
    const char* name;          /**< Name of the test case */
};

/**
 * @brief Tests solve() via hardcoded tests and prints out the results. 
 * 
 * Takes the hardcoded tests data from the solveTestData[].
 */
void testSolve();

/**
 * @brief Tests equationInput() via hardcoded tests and prints out the results. 
 * 
 */
void testEquationInput();


