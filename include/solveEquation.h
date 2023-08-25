/**
 * @file solveEquation.h
 * @brief This file contains function that solves the quadratic, linear, or constant equation based on the given coefficients.
 *
 */

#ifndef SOLVE_EQUATION_H
#define SOLVE_EQUATION_H

#include "doubleOperations.h"
#include "equationParams.h"
#include <math.h>


/**
 * @brief Solves the quadratic, linear, or constant equation based on the given coefficients.
 * 
 * This function determines the type of equation and calculates its solutions.
 * 
 * @param [in]  coefficients The coefficients of the equation.
 * @param [out] answers      Pointer to the Answers structure where solutions will be stored.
 */
void solve(const Coefficients* coefficients, Answers* answers);

#endif