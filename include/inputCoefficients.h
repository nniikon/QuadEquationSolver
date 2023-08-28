/**
 * @file inputCoefficients.h
 * @brief This file includes functions and constants that handle user input.
 */

#ifndef INPUT_COEFFICIENTS_H
#define INPUT_COEFFICIENTS_H

#include "equationParams.h"
#include "doubleOperations.h"
#include "readInput.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * @brief Enumerates the possible types of user input.
 */
enum InputType {
    COEFFICIENT_INPUT, /**< Coefficient input type */
    EQUATION_INPUT     /**< Equation input type */
};

/**
 * @brief Prompts the user to select their preferred input type.
 * 
 * @return The selected `InputType`.
 */
InputType getPreferredInput();

/**
 * @brief Prompts the user to input coefficients based on the input type.
 * 
 * @param [out] coefficients Pointer to the Coefficients structure where input coefficients will be stored.
 * @param [in]  inputType    The input type.
 */
void setCoefficients(Coefficients* coefficients, int inputType);

/**
 * @brief Asks the user if they want to continue.
 * 
 * Waits for input (y\n). Keep prompting if the user input is invalid.
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
 * @param [in]  input        The input string representing the equation.
 * 
 */
void setCoefficients_stringInput(Coefficients* coefficients, char input[]);

#endif