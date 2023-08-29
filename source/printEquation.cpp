#include "../include/printEquation.h"

// Prints a single coefficient with the following postfix (x^2, x, ).
static void printSingleCoefficient(const double coefficient, const char coefficientChar, const bool isFirstCoefficient)
{
    // If coefficient is zero...
    if (areSameDouble(coefficient, 0.0))
    {
        return; // ... don't print it.
    }
    
    char postfix[] = "ERROR!";
    switch (coefficientChar)
    {
        case 'a': strcpy(postfix, "x^2 "); break;
        case 'b': strcpy(postfix, "x ");   break;
        case 'c': strcpy(postfix, " ");    break;
        default:  assert(0);               break;
    }



    // If the coefficient goes first...
    if (isFirstCoefficient)
    {
        // ... you don't have to print '+' or any spaces between '-' and the number (eg: -x^2, 5x).
        if (isLessDouble(coefficient, 0.0))
        {   
            printf("-");
        }
    }
    else 
    {
        // In every other case we print space after signs.
        if (isGreaterDouble(coefficient, 0.0))
        {   
            printf("+ ");
        }
        else 
        {
            printf("- ");
        }
    }



    if (coefficientChar != 'c' && (areSameDouble(coefficient, 1.0) || areSameDouble(coefficient, -1.0)))
    {
        // If coefficient = +-1, no coefficient needs to be printed.
        printf("%s", postfix);
    }
    else
    {
        printf("%g%s", fabs(coefficient), postfix);
    } 
}



void printFormattedEquation(const Coefficients* coefficients)
{
    printf("\n");

    bool isA_First = false;
    bool isB_First = false;
    bool isC_First = false;

    if      (!areSameDouble(coefficients->a, 0.0)) // a != 0
        isA_First = true;
    else if (!areSameDouble(coefficients->b, 0.0)) // a == 0, b != 0
        isB_First = true;
    else if (!areSameDouble(coefficients->c, 0.0)) // a == 0, b == 0, c != 0
        isC_First = true;
    else                                           // a == 0, b == 0, c == 0;
        printf("0 = 0");

    printSingleCoefficient(coefficients->a, 'a', isA_First);
    printSingleCoefficient(coefficients->b, 'b', isB_First);
    printSingleCoefficient(coefficients->c, 'c', isC_First);
    printf("= 0\n\n");
}

void printAnswers(const Answers* answers)
{
    switch (answers->answerType) // Check by number of answers
    {
        case TWO_ROOTS:
            printf("Two real roots were found!\n");
            printf("x1 = %g\n",   answers->x1);
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
            assert(0);
            break;
    }
}