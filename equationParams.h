/**
 * @file equationParams.h
 * @brief This file defines the structures for coefficients and answers of an equation, along with associated constants and functions.
 */

#ifndef EQUATION_PARAMS_H
#define EQUATION_PARAMS_H

/**
 * @struct Coefficients
 * @brief A structure representing the coefficients of an equation.
 */
typedef struct {
    double a; /**< Coefficient of x^2 */
    double b; /**< Coefficient of x */
    double c; /**< Constant */
} Coefficients;

/**
 * @struct Answers
 * @brief A structure to store the solutions and information about the type of solutions.
 */
typedef struct {
    double x1;        /**< First root */
    double x2;        /**< Second root */
    int answerType;   /**< Type of solutions */
} Answers;

/**
 * @enum ANSWERS_TYPES
 * @brief Enumerates the possible types of solutions for an equation.
 */
enum ANSWERS_TYPES {
    NO_ROOTS,         /**< No real roots */
    ONE_ROOT,         /**< One real root */
    ONE_DOUBLE_ROOT,  /**< One double (repeated) root */
    TWO_ROOTS,        /**< Two real roots */
    INF_ROOTS         /**< Infinite roots */
};

/**
 * @brief Resets the provided coefficient and answers structures.
 * 
 * This function sets the fields of the provided Coefficients and Answers structures to zero.
 * 
 * @param [in,out] coefficients Pointer to the Coefficients structure to be reset.
 * @param [in,out] answers      Pointer to the Answers structure to be reset.
 */
void resetStructs(Coefficients* coefficients, Answers* answers);

#endif