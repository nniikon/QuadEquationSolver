#pragma once
#include "equationParams.h"
#include "doubleOperations.h"
#include <math.h>
#include <stdio.h>

/**
 * @file printEquation.h
 * @brief This file contains functions to print equation-related information.
 */

/**
 * @brief Prints out the answers of the equation.
 * 
 * This function prints the solutions of the equation stored in the `Answers` structure.
 * 
 * @param answers The answers of the equation.
 * 
 * @todo Change input to constant pointer instead of the structure. 
 */
void printAnswers(const Answers answers);

/**
 * @brief Prints the equation in the "ax^2 + bx + c" format.
 * 
 * This function uses the coefficients to print out the equation in the standard format.
 * 
 * @param coefficients The coefficients of the equation.
 * 
 * @todo Change input to constant pointer instead of the structure. 
 */
void printFormattedEquation(const Coefficients coefficients);