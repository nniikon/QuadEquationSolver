#include "print.h"
void printFormattedEquation(const Coefficients coefficients)
{
    // Handle cases where both a and b coefficients are zero.
    if (areSameDouble(coefficients.a, 0.0) && areSameDouble(coefficients.b, 0.0))
    {
        if (areSameDouble(coefficients.c, 0.0))
            printf("0 == 0\n");
        else
            printf("%g != 0\n", coefficients.c);
        return;
    }

    // a coefficient.
    if (!areSameDouble(coefficients.a, 0.0))
    {
        if (areSameDouble(coefficients.a, -1.0))
            printf("-x^2 ");
        else if (areSameDouble(coefficients.a, 1.0))
            printf("x^2 ");
        else
            printf("%gx^2 ", coefficients.a);
    }

    // b coefficient.
    if (!areSameDouble(coefficients.b, 0.0))
    {
        if (coefficients.b < 0)
            printf("- ");
        else if (!areSameDouble(coefficients.a, 0.0))
            printf("+ ");

        if (areSameDouble(coefficients.b, -1.0))
            printf("x ");
        else if (areSameDouble(coefficients.b, 1.0))
            printf("x ");
        else
            printf("%gx ", fabs(coefficients.b));
    }

    // c coefficient.
    if (!areSameDouble(coefficients.c, 0.0))
    {
        if (coefficients.c < 0)
            printf("- %g ", -coefficients.c);
        else if (!areSameDouble(coefficients.b, 0.0) || !areSameDouble(coefficients.a, 0.0))
            printf("+ %g ", coefficients.c);
        else
            printf("%g ", coefficients.c);
    }

    printf("= 0\n");
}

void printAnswers(const Answers answers)
{
    switch (answers.nAnswers) // Check by number of answers
    {
    case 2:
        printf("Two real solutions were found!\n\n");
        printf("x1 = %g\n", answers.x1);
        printf("x2 = %g\n", answers.x2);
        break;
    case 1:
        printf("Only one real solution was found!\n\n");
        printf("x = %g\n", answers.x1);
        break;
    case 0:
        printf("No solutions were found =[\n\n");
        break;
    case INF:
        printf("An infinite number of solutions were found!\n\n");
        break;
    default:
        printf("Invalid amount of solutions\n\n"); // Never occurs.
        break;
    }
}

