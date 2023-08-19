/*
Equation Input might look something like this:
5x^2 - 3x + 15 = 14 - 2x + 3x^2
5*x^2 - 15 = 0
3x^2 - 2x + 2
x - 6 = 5x + 3
x + 2x + 3*x = 5x^2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Some values to play with
#define MAX_INPUT_LENGTH 256
#define MAX_CHUNK_LENGTH 32
#define EPSILON 0.0000001
#define allowedCharacters "1234567890-+=xX*^., "
// Input types
#define COEFFICIENT_INPUT 1
#define EQUATION_INPUT 2

//#define DEBUG

typedef struct {
    double a;
    double b;
    double c;
} Coefficients;

// Prompts the user to select their preferred input type.
int askPreferredInput();
// Prompts the user to input coefficients and sets them in the provided structure.
void takeCoefficientInput(Coefficients* coefficients);
// Prompts the user to input an equation and sets the coefficients in the provided structure.
void takeEquationInput(Coefficients* coefficients);
// Prompts the user to imput a single coefficient.
void askCoefficient(double* coef, const char name);
// Checks whether the characters in the input string are among the allowed characters.
bool isCorrect(const char* input);
// Processes the input string, preparing it for2 use with the setCoefficients() function.
void normalizeEquationInput(char* input, unsigned int* inputLength);
// Removes occurrences of a specified character from the given string.
void deleteCharacter(char* input, unsigned int* inputLength, const char character);
// Takes normalized string. Sets coefficients
void setCoefficients(char* input, Coefficients* coefficients);
// Works with setCoefficients.
void setChunk(char* chunk, bool passedEqualSign, Coefficients* coefficients);
// Uses coefficients to print out the equation in the "ax^2 + bx + c" format.
void printFormattedEquation(const Coefficients coefficients);
// Uses coefficients to solve the equations. Prints out the result.
void solve(const Coefficients coefficients);
// Compares doubles.
bool areSameDouble(double f, double s);


int main()
{
	Coefficients coefficients{0, 0, 0};
	int inputType;


	inputType = askPreferredInput();
	switch(inputType)
	{
	case EQUATION_INPUT:
		takeEquationInput(&coefficients);
		break;
	case COEFFICIENT_INPUT:
		takeCoefficientInput(&coefficients);
		break;
	default:
		printf("Invalid input type\n"); // Never happens
		break;
	}

	printFormattedEquation(coefficients);

    solve(coefficients);
}


int askPreferredInput() {
    char inputBuffer[100];  // Buffer for input

    while (1) {
        // Display the menu of choices
        printf("What type of input would you prefer?\n"
               "(1) Coefficient input\n"
               "(2) Equation input\n");

        // Read the user's input
        scanf("%s", inputBuffer);
        int choice = inputBuffer[0];  // Take the first character

        // Check the user's choice and return the corresponding input type
        if (choice == '1') {
            return COEFFICIENT_INPUT;
        } else if (choice == '2') {
            return EQUATION_INPUT;
        } else {
            // Invalid input, inform the user and loop again
            printf("Invalid input. Please choose 1 or 2.\n");
        }
    }
}


void takeEquationInput(Coefficients* coefficients)
{
    while (getchar() != '\n'); // Clear the input buffer.

    char input[MAX_INPUT_LENGTH];
    do
    {
        printf("Enter your equation: ");
        scanf("%[^\n]", input);
        
        if (!isCorrect(input))
        {
            printf("Invalid input.\n");
            input[0] = '\n'; // Clear the input.
            while (getchar() != '\n'); // Clear the input buffer.
        }
    } while (!isCorrect(input)); // Repeat until valid input is received.

    unsigned int inputLength = strlen(input);

    // Prepare the equation input.
    normalizeEquationInput(input, &inputLength);

    // Set the coefficients
    setCoefficients(input, coefficients);

    #ifdef DEBUG
        printf("\nDEBUG: standardized equation: %s\n", input);
        printf("DEBUG: a = %f \nDEBUG: b = %f \nDEBUG: c = %f\n\n", a, b, c);
    #endif
}

bool isCorrect(const char* input)
{
    bool isListed;

    // Iterate through the input string.
    for (unsigned int i = 0; i < strlen(input); i++)
    {
        isListed = false;

        // Check if the current character is among the allowed characters.
        for (unsigned int j = 0; j < strlen(allowedCharacters); j++)
        {
            if (input[i] == allowedCharacters[j])
            {
                isListed = true;
                break;
            }
        }

        // If the current character is not in the allowed list, return false.
        if (!isListed)
            return false;
    }

    // If all characters are among the allowed ones, return true.
    return true;
}

void deleteCharacter(char* input, unsigned int* inputLength, const char character)
{
    int currentEmptySpace = 0;  // Tracks the current position for the next character to be moved to.

    // Iterate through the input string.
    for (unsigned int i = 0; i < *inputLength; i++)
    {
        // If the current character is not the character to be deleted...
        if (input[i] != character)
        {
            // Move the current character to the position of the current "empty" space and increment it.
            input[currentEmptySpace] = input[i];
            currentEmptySpace++;
        }
    }

    // Update the input length after deleting characters.
    *inputLength = currentEmptySpace;

    // Add the null terminator to the end of the modified string to ensure it remains valid.
    input[currentEmptySpace] = '\0';
}

void normalizeEquationInput(char* input, unsigned int* inputLength)
{
    // A normalized equation string should look something like:

    // 5x^2-6x+12=5x-12x^2

    // Remove unnecessary characters (it will decrease inputLength)
    deleteCharacter(input, inputLength, ' ');
    deleteCharacter(input, inputLength, '*');

    // Replace similar characters
    for (unsigned int i = 0; i < *inputLength; i++)
    {
        switch(input[i])
        {
        case 'X':
            input[i] = 'x';
            break;
        case ',':
            input[i] = '.';
            break;
		default:
			// it's not needed
			break;
        }
    }
}

void setChunk(char* chunk, bool passedEqualSign, Coefficients* coefficients)
{
    // A chunk should look something like:

    // +5x^2    x   -x^2    -6.5

    bool isA = false,
         isB = false,
         isC = false;
    double value = 0.0;
    unsigned len = strlen(chunk);

    // Determine which coefficient (a, b, or c) the value will be added to.

    // If the chunk ends with x^2, add to 'a' coefficient.
    if (len >= 3 && chunk[len - 3] == 'x' && chunk[len - 2] == '^' && chunk[len - 1] == '2')
    {
        isA = true;

        // Handle cases like x^2, +x^2, -x^2
        if ((len == 3) || (len == 4 && (chunk[0] == '-' || chunk[0] == '+')))
        {
            chunk[len - 3] = '1'; // Replace 'x' with 1
        }
    }
    // If the chunk ends with x, add to 'b' coefficient.
    else if (len >= 1 && chunk[len - 1] == 'x')
    {
        isB = true;

        // Handle cases like x, +x, -x
        if ((len == 1) || (len == 2 && (chunk[0] == '-' || chunk[0] == '+')))
        {
            chunk[len - 1] = '1'; // Replace 'x' with 1
        }
    }
    // Otherwise, treat it as a constant and add to 'c' coefficient.
    else
    {
        isC = true;
    }

    // Set the value from the chunk.
    value = atof(chunk);

    // If on the right-hand side of the equation, negate the value.
    if (passedEqualSign)
    {
        value = -value;
    }

    // Add the value to the appropriate coefficient.
    if (isA)
    {
        coefficients->a += value;
        return;
    }
    if (isB)
    {
        coefficients->b += value;
        return;
    }
    if (isC)
    {
        coefficients->c += value;
        return;
    }
}

void setCoefficients(char* input, Coefficients* coefficients)
{
    bool passedEqualSign = false;  // Flag to track whether the equal sign has been encountered
    int len = strlen(input);        // Length of the input string
    char strChunk[MAX_CHUNK_LENGTH]{};  // Temporary buffer to store chunks of the string
    int chunkCounter = 0;           // Counter for the buffer index

    // Iterate through the input string
    for (int i = 0; i <= len; i++)
    {
        // If a delimiter is encountered (+, -, =, \0)
        if (input[i] == '+' || input[i] == '-' || input[i] == '=' || input[i] == '\0')
        {
            strChunk[chunkCounter] = '\0';  // Terminate the string in the buffer
            chunkCounter = 0;  // Reset the counter for the next chunk
            setChunk(strChunk, passedEqualSign, coefficients);  // Process the chunk

            // If the current symbol is the equal sign, set the flag
            if (input[i] == '=')
            {
                passedEqualSign = true;
                continue; // Skip iteration to prevent equal sign from interfering with processing
            }
        }

        strChunk[chunkCounter] = input[i];  // Add the character to the buffer
        chunkCounter++;  // Increment the buffer counter
    }
}


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

bool areSameDouble(double f, double s)
{
	return fabs(f - s) < EPSILON;
}

void solve(const Coefficients coefficients)
{
    // Check if it's a quadratic equation (a is not zero).
    if (!areSameDouble(coefficients.a, 0.0))
    {
        double d = coefficients.b * coefficients.b - 4 * coefficients.a * coefficients.c; // Calculate the discriminant.

        // Check the value of the discriminant.
        if (d > 0)
        {
            printf("Two real solutions were found!\n");
            printf("x1 = %g\n", (-coefficients.b + sqrt(d)) / (2.0 * coefficients.a)); // Calculate and print the first root.
            printf("x2 = %g\n", (-coefficients.b - sqrt(d)) / (2.0 * coefficients.a)); // Calculate and print the second root.
        }
        else if (areSameDouble(d, 0.0)) // Check if discriminant is close to zero.
        {
            printf("Only one real solution was found!\n");
            printf("x = %g\n", -coefficients.b / (2.0 * coefficients.a)); // Calculate and print the only root.
        }
        else
        {
            printf("No real solutions were found\n"); // No real roots.
        }
    }
    else if (!areSameDouble(coefficients.b, 0.0)) // Linear equation (a is zero, b is not zero).
    {
        printf("Only one real solution was found\n");
        printf("x = %g\n", -(coefficients.c / coefficients.b)); // Calculate and print the linear root.
    }
    else // Constant equation (a and b are zero).
    {
        if (areSameDouble(coefficients.c, 0.0)) // Check if the constant term is almost zero.
        {
            printf("An infinite number of solutions were found!\n"); // Infinite solutions.
        }
        else
        {
            printf("No solutions were found =(\n"); // No solutions (constant is non-zero).
        }
    }
}

void askCoefficient(double* coef, const char name)
{
    int validInput = 0; // Flag to track whether the input is valid.

    // A loop that keeps prompting the user until valid input is provided.
    do
    {
        printf("Please enter coefficient %c: ", name);
        validInput = scanf("%lf", coef); // Attempt to read a double from the user's input.

        #ifdef DEBUG
            printf("validInput: %d\nNumber %c = %f\n", validInput, name ,*coef);
        #endif

        if (validInput == 0)
        {
            printf("Invalid input.\n");
            while (getchar() != '\n'); // Clear the input buffer.
        }
    } while (validInput == 0); // Continue the loop as long as the input is invalid.

    // Clear the input buffer.
    while (getchar() != '\n');
}

void takeCoefficientInput(Coefficients* coefficients)
{
	// Clean the input buffer.
	while(getchar() != '\n');

	askCoefficient(&(coefficients->a), 'a');
    askCoefficient(&(coefficients->b), 'b');
    askCoefficient(&(coefficients->c), 'c');
}