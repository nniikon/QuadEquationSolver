/*
Equation Input might look something like this:
5x^2 - 3*x + 15 = 14 - 2x + 3x^2
5*x^2 - 15 = 0
3x^2 - 2x + 2
x - 6 = 5x + 3
x + 2x + 3*x = 5x^2
*/

#include "input.h"
#include "print.h"
#include "solve.h"

int main()
{

		Coefficients coefficients{0, 0, 0};
		Answers answers{0, 0, 0};
		int inputType;

		inputType = askPreferredInput();

	do
	{
		resetStructs(&coefficients, &answers);

		takeInput(&coefficients, inputType);

		printFormattedEquation(coefficients);

		solve(coefficients, &answers);

		printAnswers(answers);

	} while(wantToContinue());
}



