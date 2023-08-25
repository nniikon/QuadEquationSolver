/**
 * @file inputCoefficients.h
 * @brief This file contains functions and constants 
 */

#ifndef INPUT_COEFFICIENTS_H
#define INPUT_COEFFICIENTS_H

#include "equationParams.h"
#include "doubleOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Enumerates the possible types of user input.
 */
enum INPUT_TYPE {
    COEFFICIENT_INPUT, /**< Coefficient input type */
    EQUATION_INPUT     /**< Equation input type */
};

/**
 * @brief Prompts the user to select their preferred input type.
 * 
 * @return The selected `INPUT_TYPE`.
 */
INPUT_TYPE askPreferredInput();

/**
 * @brief Prompts the user to input coefficients based on the input type.
 * 
 * @param [out] coefficients Pointer to the Coefficients structure where input coefficients will be stored.
 * @param [in]  inputType    The input type.
 */
void takeInput(Coefficients* coefficients, int inputType);

/**
 * @brief Asks the user if they want to continue.
 * 
 * Waits for input (y\n). Keep prompting if user's input is invalid.
 * 
 * @return `true` if the user wants to continue, `false` otherwise.
 */
bool wantToContinue();

/**
 * @brief Converts equation input to coefficients.
 * 
 * This function sets the coefficients in the provided structure based on the provided input.
 * 
 * @param [out] coefficients Pointer to the `Coefficients` structure where coefficients will be stored.
 * @param [in] input The input string representing the equation.
 * 
 */
void equationInputToCoefficients(Coefficients* coefficients, char input[]);

#endif