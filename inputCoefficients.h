#pragma once
#include "equationParams.h"
#include "doubleOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file inputCoefficients.h
 * @brief This file contains functions and constants 
 * 
 */

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
 * @return The selected input type.
 */
int askPreferredInput();

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
 * @return `true` if the user wants to continue, `false` otherwise.
 */
bool wantToContinue();

/**
 * @brief Converts equation input to coefficients.
 * 
 * This function sets the coefficients in the provided structure based on the provided input.
 * 
 * @param [out] coefficients Pointer to the Coefficients structure where coefficients will be stored.
 * @param [in] input The input string representing the equation.
 */
void equationInputToCoefficients(Coefficients* coefficients, char input[]);
