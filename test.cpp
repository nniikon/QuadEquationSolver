#include "test.h"

static void testSingleSolve(Coefficients coefficients, Answers answersRef)
{
	static int counter = 1;
	Answers answers = {0, 0, 0};

	solve(coefficients, &answers);

	// Two roots
	if (answersRef.answerType == TWO_ROOTS)
	{
		if (answersRef.answerType == answers.answerType &&
			areSameDouble(answersRef.x1, answers.x1) &&
			areSameDouble(answersRef.x2, answers.x2) )
		{
			printf("Solve Test %d passed\n", counter);
		} 
		else
		{
			printf("SOLVE TEST %d FAILED\n", counter);
			printf("x1 = %g\nx2 = %g\n", answers.x1, answers.x2);
			printf("Expected x1 = %g\nExpected x2 = %g\n", answersRef.x1, answersRef.x2);
		}
	}
	// One root
	else if (answersRef.answerType == ONE_ROOT || answersRef.answerType == ONE_DOUBLE_ROOT)
	{
		if (answersRef.answerType == answers.answerType &&
			areSameDouble(answersRef.x1, answers.x1) )
		{
			printf("Solve Test %d passed\n", counter);
		} 
		else
		{
			printf("SOLVE TEST %d FAILED\n", counter);
			printf("x1 = %g\n", answers.x1);
			printf("Expected x1 = %g\n", answersRef.x1);
		}
	}
	// No roots
	else
	{
		if (answersRef.answerType == answers.answerType)
		{
			printf("Solve Test %d passed\n", counter);
		} 
		else
		{
			printf("SOLVE TEST %d FAILED\n", counter);
		}
	}
	counter++;
}

void testSolve()
{
	testSingleSolve((Coefficients) {3, -5, 2},  (Answers) {1.0, 0.66666666666666, TWO_ROOTS});
	testSingleSolve((Coefficients) {10, -5, -5},(Answers) {1.0, -0.5, TWO_ROOTS});
	testSingleSolve((Coefficients) {1, 2, 1},   (Answers) {-1.0, 0, ONE_DOUBLE_ROOT});
	testSingleSolve((Coefficients) {1, -2, 1},  (Answers) {1.0, 0, ONE_DOUBLE_ROOT});
	testSingleSolve((Coefficients) {0, 1, 1},   (Answers) {-1.0, 0, ONE_ROOT});
	testSingleSolve((Coefficients) {0, 5, -1},  (Answers) {0.2, 0, ONE_ROOT});
}

// Compares the output of the program's equation solver with expected coefficients.
static void testSingleEquationInput(char input[], Coefficients coefficientsRef) 
{
    static int counter = 1;
    Coefficients coefficients = {0, 0, 0};
    
	// Run the code that's being tested.
	equationInputToCoefficients(&coefficients, input);

        // Compare with the expected values.
        if (areSameDouble(coefficients.a, coefficientsRef.a) &&
            areSameDouble(coefficients.b, coefficientsRef.b) &&
            areSameDouble(coefficients.c, coefficientsRef.c)) 
        {
            printf("EquationInput Test %d passed.\n", counter);
        }
        else 
        {
            printf("\nEquationInput TEST FAILED.\n");
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