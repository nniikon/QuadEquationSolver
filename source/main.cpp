/*
Equation Input might look something like this:
5x^2 - 3*x + 15 = 14 - 2x + 3x^2
5*x^2 - 15 = 0
3x^2 - 2x + 2
x - 6 = 5x + 3
x + 2x + 3*x = 5x^2
*/

//#define TEST
//#define LOG

#include "../include/test.h"
#include "../include/inputCoefficients.h"
#include "../include/printEquation.h"
#include "../include/solveEquation.h"

/*
TODO:
0) start the program
4) Try cloning assert;
5) Use assert;
*/


int main()
{
	#ifdef TEST
		testEquationInput();
		testSolve();
	#else

	do
	{
		INPUT_TYPE inputType = askPreferredInput();

		Coefficients coefficients{0.0, 0.0, 0.0};
		Answers      answers{0.0, 0.0, NO_ROOTS};

		takeInput(&coefficients, inputType);

		printFormattedEquation(&coefficients);

		solve(&coefficients, &answers);

		printAnswers(&answers);

	} while(wantToContinue());

	#endif
}
