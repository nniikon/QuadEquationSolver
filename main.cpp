/*
Equation Input might look something like this:
5x^2 - 3*x + 15 = 14 - 2x + 3x^2
5*x^2 - 15 = 0
3x^2 - 2x + 2
x - 6 = 5x + 3
x + 2x + 3*x = 5x^2
*/

#include "test.h"
#include "inputCoefficients.h"
#include "printEquation.h"
#include "solveEquation.h"
#include <iostream>
/*
TODO:
-1) Write TODO list;                             +
0) use VSCode;                                   +
1) Change file names;                            +
2) Kill consts.h;                                +
3) Come up with an alternative for #pragma once; +

#if !defined(ABC)
#define ABC
	I was close =)
#endif

4) Try cloning assert;
5) Use assert;
6) Add different types of singleROOT feature;    +
7) CodeStyle for commits;                        +
8) Fix some equation input bugs;                 +
9) Use Doxygen to document functions;            +
10) Fix unit-tests.                              +
11) Use "const Struct* struct" instead of "Struct struct"
*/

//#define TEST

int main()
{
	#ifdef TEST
		testEquationInput();
		testSolve();
	#endif

	Coefficients coefficients{0, 0, 0};
	Answers answers{0, 0, 0};

	do
	{
		int inputType = askPreferredInput();

		resetStructs(&coefficients, &answers);

		takeInput(&coefficients, inputType);

		printFormattedEquation(coefficients);

		solve(coefficients, &answers);

		printAnswers(answers);

	} while(wantToContinue());
}
