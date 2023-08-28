/**
 * @file doubleOperations.h
 * @brief This file contains constants and functions related to floating-point variables operations.
 */

#ifndef DOUBLE_OPERATIONS_H
#define DOUBLE_OPERATIONS_H

#include "math.h"


/**
 * @brief A small constant used for floating-point comparison.
 */
const double EPSILON = 1e-6;


/**
 * @brief Compares two floating-point numbers for equality within a small epsilon.
 * 
 * This function checks if the difference between two floating-point numbers is within the defined EPSILON.
 * 
 * @param f The first number.
 * @param s The second number.
 * 
 * @return `true` if the numbers are considered equal, `false` otherwise.
 */
bool areSameDouble(double f, double s);


/**
 * @brief Compares two floating-point numbers within a small epsilon.
 * 
 * This function checks if the first floation-point number is greater than the second float-point number within the defined EPSILON.
 * 
 * @param f The first number.
 * @param s The second number.
 * 
 * @return `true` if the first number is greater than the second number, `false` otherwise.
 */
bool isGreaterDouble(double f, double s);


/**
 * @brief Compares two floating-point numbers within a small epsilon.
 * 
 * This function checks if the first floation-point number is less than the second float-point number within the defined EPSILON.
 * 
 * @param f The first number.
 * @param s The second number.
 * 
 * @return `true` if the first number is less than the second number, `false` otherwise.
 */
bool isLessDouble(double f, double s);


#endif