#include "solveEquation.h"
void solve(const Coefficients coefficients, Answers* answers)
{
    // Check if it's a quadratic equation (a is not zero).
    if (!areSameDouble(coefficients.a, 0.0))
    {
        double d = coefficients.b * coefficients.b - 4 * coefficients.a * coefficients.c; // Calculate the discriminant.

        // Check the value of the discriminant.
        if (d > 0)
        {
            answers->answerType = TWO_ROOTS;
            answers->x1 = (-coefficients.b + sqrt(d)) / (2.0 * coefficients.a);
            answers->x2 = (-coefficients.b - sqrt(d)) / (2.0 * coefficients.a);
        }
        else if (areSameDouble(d, 0.0)) // Check if discriminant is close to zero.
        {
            answers->answerType = ONE_DOUBLE_ROOT;
            answers->x1 = (-coefficients.b) / (2.0 * coefficients.a);
        }
        else // Discriminant is negative.
        {
            answers->answerType = NO_ROOTS;
        }
    }
    else if (!areSameDouble(coefficients.b, 0.0)) // Linear equation (a is zero, b is not).
    {
        answers->answerType = ONE_ROOT;
        answers->x1 = -(coefficients.c / coefficients.b);
    }
    else // Constant equation (a and b are zero).
    {
        if (areSameDouble(coefficients.c, 0.0)) // Check if the constant term is almost zero.
        {
            answers->answerType = INF_ROOTS;
        }
        else
        {
            answers->answerType = 0;
        }
    }
}
