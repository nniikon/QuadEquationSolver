#include "../include/test.h"
#include "../include/inputCoefficients.h"
#include "../include/printEquation.h"
#include "../include/solveEquation.h"

//#define TEST
//#define LOG


int main()
{
	#ifdef TEST
		testEquationInput();
		testSolve();
	#else

	do
	{
		INPUT_TYPE inputType = getPreferredInput();

		Coefficients coefficients{0.0, 0.0,   0.0   };
		Answers      answers     {0.0, 0.0, NO_ROOTS};

		setCoefficients(&coefficients, inputType);

		printFormattedEquation(&coefficients);

		solve(&coefficients, &answers);

		printAnswers(&answers);

	} while(wantToContinue());

	#endif
}
