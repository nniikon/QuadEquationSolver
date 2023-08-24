#include "inputCoefficients.h"

// Removes occurrences of a specified character from the given string.
static void deleteCharacter(char* input, unsigned int* inputLength, const char character)
{
	// Tracks the current position for the next character to be moved to.
    int currentEmptySpace = 0;

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


// Checks whether the characters in the input string are among the allowed characters.
static bool hasOnlyAllowedCharacters(const char* input, const char* allowedCharacters)
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


// Checks if the given string has the character in it.
static bool hasCharacterInString(char character, const char input[])
{
    for (size_t i = 0; i < strlen(input); i++)
	{
        if (character == input[i])
        {
            return true;
        }
    }
    return false;
}


// Returns true if every given character in the string has at least one of the other given characters around.
static bool hasSymbolsAround(char input[], char givenCharacter, const char aroundCharacters[])
{
	for(size_t i = 0; i < strlen(input) - 1; i++)
	{
		if(input[i] == givenCharacter)
		{
			// Check if the symbol is to the left.
			bool isToTheLeft = (i >= 1) && hasCharacterInString(input[i - 1], aroundCharacters);

			// Check if the symbol is to the right.
			bool isToTheRight = hasCharacterInString(input[i + 1], aroundCharacters);

			// If its neither to the left nor to the right...
			if (!(isToTheLeft || isToTheRight))
			{
				return false; // FAIL
			}
		}
	}
	return true;
}


// Returns true if every given character in the string doens't have restricted characters around.
static bool hasRestrictedSymbolsAround(char input[], char givenCharacter, const char aroundCharacters[])
{
	for(size_t i = 0; i < strlen(input) - 1; i++)
	{
		if(input[i] == givenCharacter)
		{
			// Check if the symbol is to the left.
			bool isToTheLeft = (i >= 1) && hasCharacterInString(input[i - 1], aroundCharacters);

			// Check if the symbol is to the right.
			bool isToTheRight = hasCharacterInString(input[i + 1], aroundCharacters);

			// If its neither to the left nor to the right...
			if (isToTheLeft || isToTheRight)
			{
				return false; // FAIL
			}
		}
	}
	return true;
}


// Calculates length of the langest chunk in the given string
static int maxChunkLength(const char* input)
{
	int strSize = 0;
	int maxSize = 0;
	// Iterate through the input string
	for (size_t i = 0; i <= strlen(input); i++)
	{
		strSize++;

		if (input[i] == '\0' || hasCharacterInString(input[i], DELIMITER)) // If it hits a delimiter...
		{
			if (strSize > maxSize)
				maxSize = strSize;

			strSize = 0; // Reset the size
		}
	}
	return maxSize;
}


// Checks if the given string is correct and can be used to set coefficients
static bool isCorrect(char input[])
{
	if (!hasSymbolsAround(input, ' ', ALLOWED_AROUND_SPACE_CHARACTERS))
	{
		return false;
	}
	if (!( hasRestrictedSymbolsAround(input, 'x', RESTRICTED_AROUND_X_CHARACTERS) &&
	       hasRestrictedSymbolsAround(input, 'X', RESTRICTED_AROUND_X_CHARACTERS) )  )
	{
		return false;
	}
	if (maxChunkLength(input) >= 32)
	{
		return false;
	}
	if (!hasOnlyAllowedCharacters(input, ALLOWED_EQUATION_INPUT_CHARACTERS))
	{
		return false;
	}
	return true;
}



// Processes the input string, preparing it for use with the setCoefficients() function.
static void normalizeEquationInput(char* input, unsigned int* inputLength)
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
			// do nothing
			break;
        }
    }
}


// Works with setCoefficients.
static void setChunk(char* chunk, bool passedEqualSign, Coefficients* coefficients)
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


// Takes normalized string. Sets coefficients
static void setCoefficients(char* input, Coefficients* coefficients)
{
    bool passedEqualSign = false;  // Flag to track whether the equal sign has been encountered
    int len = strlen(input);        // Length of the input string
    char strChunk[MAX_CHUNK_LENGTH]{};  // Temporary buffer to store chunks of the string
    int chunkCounter = 0;           // Counter for the buffer index

    // Iterate through the input string
    for (int i = 0; i <= len; i++)
    {
        // If a delimiter is encountered (+, -, =, \0)
        if (input[i] == '\0' || hasCharacterInString(input[i], DELIMITER))
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


// Prompts the user to input a single coefficient.
static void askCoefficient(double* coef, const char name)
{
	char buffer[MAX_CHUNK_LENGTH]; // Buffer to store user's input.
    double validNumber = 0;
	bool isValid = false;
    // A loop that keeps prompting the user until valid input is provided.
    do
    {
        printf("Please enter coefficient %c: ", name);
        scanf("%[^\n]", buffer); // Read a string from the user's input.
		validNumber = atof(buffer); // Attempt to read a double from the buffer.
		isValid = hasOnlyAllowedCharacters(buffer, ALLOWED_COEFFICIENT_INPUT_CHARACTERS);

        if (!isValid)
        {
            printf("Invalid input.\n");
            // Clear the input buffer.
            while (getchar() != '\n')
			    ; 
        }

    } while (!isValid); // Continue the loop as long as the input is invalid.

	*coef = validNumber; // Set the coefficient.
    // Clear the input buffer.
}


// Prompts the user to input coefficients and sets them in the provided structure.
static void takeCoefficientInput(Coefficients* coefficients)
{
	// Clean the input buffer.
	while(getchar() != '\n')
        ;

	askCoefficient(&(coefficients->a), 'a');

	while (getchar() != '\n')
		;

    askCoefficient(&(coefficients->b), 'b');

    while (getchar() != '\n')
		;

    askCoefficient(&(coefficients->c), 'c');
}


// 
static void setEquationInput(char input[])
{
    // Clear the input buffer.
    while (getchar() != '\n')
		; 

    do
    {
        printf("Enter your equation: ");
        scanf("%[^\n]", input);

        if (!isCorrect(input))
        {
            printf("Invalid input.\n");
            input[0] = '\n'; // Clear the input.

            // Clear the input buffer.
            while (getchar() != '\n')
			    ; 
        }
    } while (!isCorrect(input)); // Repeat until valid input is received.
}


// Sets coefficients, takes a correct string as input.
void equationInputToCoefficients(Coefficients* coefficients, char input[])
{
    unsigned int inputLength = strlen(input);

    // Prepare the equation input.
    normalizeEquationInput(input, &inputLength);

    // Set the coefficients
    setCoefficients(input, coefficients);
}


int askPreferredInput() {
    char inputBuffer[MAX_CHUNK_LENGTH];  // Buffer for input

    while (true) {
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
            // Clear the input buffer.
			while (getchar() != '\n')
			    ;
        }
    }
}


// Promts user to enter the equation and sets the corresponding coefficients. 
static void takeEquationInput(Coefficients* coefficients)
{
    char input[MAX_INPUT_LENGTH];
    setEquationInput(input);
    equationInputToCoefficients(coefficients, input);
}


void takeInput(Coefficients* coefficients, int inputType)
{
	switch(inputType)
	{
	case EQUATION_INPUT:
		takeEquationInput(coefficients);
		break;
	case COEFFICIENT_INPUT:
		takeCoefficientInput(coefficients);
		break;
	default:
		printf("Invalid input type\n"); // Never occurs.
		break;
	}
}


bool wantToContinue()
{
    char input[MAX_CHUNK_LENGTH];
    while (true)
	{
		// Clear the input buffer.
		while (getchar() != '\n')
			;

        printf("Do you want to solve another equation? (y/n): ");
        scanf("%[^\n]", input);

        // Check if the input is correct
		if(hasOnlyAllowedCharacters(input, ALLOWED_CONTINUE_INPUT_CHARACTERS) && strlen(input) == 1)
		{
			if (input[0] == 'y' || input[0] == 'Y')
				return true;
			else if (input[0] == 'n' || input[0] == 'N')
				return false;
			else
			{
				// Shouldn't occure
				printf("ERROR. Invalid input. Please enter 'y' or 'n'.\n");
			}
		}
		else
		{
			printf("Invalid input. Please enter 'y' or 'n'.\n");
		}
    }
}