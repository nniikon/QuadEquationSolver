/**
 * @file printEquation.h
 * @brief This file contains functions to print equation-related information.
 */

#ifndef PRINT_EQUATION_H
#define PRINT_EQUATION_H

#include "equationParams.h"
#include "doubleOperations.h"
#include <math.h>
#include <stdio.h>

/**
 * @brief Prints out the answers of the equation.
 * 
 * This function prints the solutions of the equation stored in the `Answers` structure.
 * 
 * @param answers The answers of the equation.
 * 
 */
void printAnswers(const Answers* answers);

/**
 * @brief Prints the equation in the "ax^2 + bx + c" format.
 * 
 * This function uses the coefficients to print out the equation in the standard format.
 * 
 * @param coefficients The coefficients of the equation.
 * 
 */
void printFormattedEquation(const Coefficients* coefficients);

#endif