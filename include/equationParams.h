/**
 * @file equationParams.h
 * @brief This file defines the structures for coefficients and answers of an equation, along with associated constants and functions.
 */


#ifndef EQUATION_PARAMS_H
#define EQUATION_PARAMS_H


/**
 * @enum ANSWER_TYPE
 * @brief Enumerates the possible types of solutions for an equation.
 */
enum ANSWER_TYPE {
    NO_ROOTS,        /**< No real roots */
    ONE_ROOT,        /**< One real root */
    ONE_DOUBLE_ROOT, /**< One double (repeated) root */
    TWO_ROOTS,       /**< Two real roots */
    INF_ROOTS        /**< Infinite roots */
};


/**
 * @struct Coefficients
 * @brief A structure representing the coefficients of an equation.
 */
struct Coefficients {
    double a; /**< Coefficient of x^2 */
    double b; /**< Coefficient of x */
    double c; /**< Constant coefficient*/
};


/**
 * @struct Answers
 * @brief A structure to store the solutions and information about the type of solutions.
 */
struct Answers{
    double x1;               /**< First root */
    double x2;               /**< Second root */
    ANSWER_TYPE answerType; /**< Type of solutions */
};


#endif