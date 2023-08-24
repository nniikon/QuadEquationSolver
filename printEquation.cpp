#include "printEquation.h"
void printFormattedEquation(const Coefficients* coefficients)
{
    printf("\n");
	// Careful govnokod
    // Handle cases where both a and b coefficients are zero.
    if (areSameDouble(coefficients->a, 0.0) && areSameDouble(coefficients->b, 0.0))
    {
        if (areSameDouble(coefficients->c, 0.0))
            printf("0 == 0\n");
        else
            printf("%g != 0\n", coefficients->c);
        return;
    }

    // a coefficient.
    if (!areSameDouble(coefficients->a, 0.0))
    {
        if (areSameDouble(coefficients->a, -1.0))
            printf("-x^2 ");
        else if (areSameDouble(coefficients->a, 1.0))
            printf("x^2 ");
        else
            printf("%gx^2 ", coefficients->a);
    }

    // b coefficient.
    if (!areSameDouble(coefficients->b, 0.0))
    {
        if (coefficients->b < 0 && !areSameDouble(coefficients->a, 0.0))
            printf("- ");
		else if (coefficients->b < 0 && areSameDouble(coefficients->a, 0.0))
			printf("-");
        else if (!areSameDouble(coefficients->a, 0.0))
            printf("+ ");

        if (areSameDouble(coefficients->b, -1.0))
            printf("x ");
        else if (areSameDouble(coefficients->b, 1.0))
            printf("x ");
        else
            printf("%gx ", fabs(coefficients->b));
    }

    // c coefficient.
    if (!areSameDouble(coefficients->c, 0.0))
    {
        if (coefficients->c < 0)
            printf("- %g ", -coefficients->c);
        else if (!areSameDouble(coefficients->b, 0.0) || !areSameDouble(coefficients->a, 0.0))
            printf("+ %g ", coefficients->c);
        else
            printf("%g ", coefficients->c);
    }

    printf("= 0\n\n");
}

void printAnswers(const Answers* answers)
{
    switch (answers->answerType) // Check by number of answers
    {
    case TWO_ROOTS:
        printf("Two real roots were found!\n");
        printf("x1 = %g\n", answers->x1);
        printf("x2 = %g\n\n", answers->x2);
        break;
    case ONE_ROOT:
        printf("Only one real root was found!\n");
        printf("x = %g\n\n", answers->x1);
        break;
    case ONE_DOUBLE_ROOT:
        printf("One real repeated root was found!\n");
        printf("x = %g\n\n", answers->x1);
        break;
    case NO_ROOTS:
        printf("No real roots were found =[\n\n");
        break;
    case INF_ROOTS:
        printf("An infinite number of roots were found!\n\n");
        break;
    default:
        printf("Invalid amount of roots\n\n"); // Never occurs.
        break;
    }
}

