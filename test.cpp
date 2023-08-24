#include "test.h"

// Variable for test numbering.
int counter = 1;


static bool compareAnswers(const Answers* a, const Answers* b)
{
	if (!areSameDouble(a->answerType, b->answerType))
		return false;
	if (a->answerType == TWO_ROOTS)
		return (areSameDouble(a->x1, b->x1) && areSameDouble(a->x2, b->x2));
	else if (a->answerType == ONE_DOUBLE_ROOT || a->answerType == ONE_ROOT)
		return areSameDouble(a->x1, b->x1);
	else if (a->answerType == NO_ROOTS || a->answerType == INF_ROOTS)
		return true;
	else
		assert(0);
}


void testSolve()
{
	// Test data.
	const SolveTestData solveTestData[] = {
    	{(Coefficients){     3.0,    -5.0,     2.0},  (Answers){     1.0, 2.0/3.0,        TWO_ROOTS},  "TWO ROOTS SOLVE TEST"},
    	{(Coefficients){    10.0,    -5.0,    -5.0},  (Answers){     1.0,    -0.5,        TWO_ROOTS},  "TWO ROOTS SOLVE TEST"},
    	{(Coefficients){     1.0,     2.0,     1.0},  (Answers){    -1.0,     0.0, ONE_DOUBLE_ROOT}, "DOUBLE ROOT SOLVE TEST"},
    	{(Coefficients){     1.0,    -2.0,     1.0},  (Answers){     1.0,     0.0, ONE_DOUBLE_ROOT}, "DOUBLE ROOT SOLVE TEST"},
    	{(Coefficients){     0.0,     1.0,     1.0},  (Answers){    -1.0,     0.0,        ONE_ROOT},    "ONE ROOT SOLVE TEST"},
    	{(Coefficients){     0.0,     5.0,    -1.0},  (Answers){     0.2,     0.0,        ONE_ROOT},    "ONE ROOT SOLVE TEST"},
    	{(Coefficients){     1.0,     2.0,     3.0},  (Answers){     0.0,     0.0,        NO_ROOTS},    "NO ROOTS SOLVE TEST"},
    	{(Coefficients){     2.0,     3.0,   100.0},  (Answers){     0.0,     0.0,        NO_ROOTS},    "NO ROOTS SOLVE TEST"},
	};

	int nSolveTests = (int) (sizeof(solveTestData) / sizeof(SolveTestData));

	for (int i = 0; i < nSolveTests; i++)
	{
		Answers answers = {0, 0, 0};

		solve(solveTestData[i].coefficients, &answers);

		if (compareAnswers(&solveTestData[i].answers, &answers))
		{
			printf("%25s num %2d passed\n", solveTestData[i].name, counter);
		}
		else
		{
			printf("\n%s num %d FAILED FAILED FAILED FAILED WARNING!\n\n", solveTestData[i].name, counter);
		}
	counter += 1;
	}
}

// Compares the output of the program's equation solver with expected coefficients.
static void testSingleEquationInput(char input[], Coefficients coefficientsRef) 
{
    Coefficients coefficients = {0, 0, 0};
    
	// Run the code that's being tested.
	equationInputToCoefficients(&coefficients, input);

        // Compare with the expected values.
        if (areSameDouble(coefficients.a, coefficientsRef.a) &&
            areSameDouble(coefficients.b, coefficientsRef.b) &&
            areSameDouble(coefficients.c, coefficientsRef.c)) 
        {
            printf("%25s num %2d passed\n", "EQUATION INPUT TEST", counter);
        }
        else 
        {
            printf("\nEquationInput TEST FAILED\n");
            printf("Input value: %s\n", input);
            printf("a = %g, expected a = %g\n", coefficients.a, coefficientsRef.a);
            printf("b = %g, expected b = %g\n", coefficients.b, coefficientsRef.b);
            printf("c = %g, expected c = %g\n", coefficients.c, coefficientsRef.c);
        }
    counter++;
}


// Function to test equation input handling.
void testEquationInput() 
{
    char equation1[] = "x^2 - 5x + 12 = -x^2 - x + 5";
    testSingleEquationInput(equation1, (Coefficients){2, -4, 7});
    char equation2[] = "x^2 - x^2 = x - x + 1.23";
    testSingleEquationInput(equation2, (Coefficients){0, 0, -1.23});
    char equation3[] = "5x^2 - 2x^2 = 6.43x - 5.43x + 1.11";
    testSingleEquationInput(equation3, (Coefficients){3, -1, -1.11});
}