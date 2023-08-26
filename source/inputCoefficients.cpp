#include "../include/inputCoefficients.h"
#include <assert.h>

// Characters that are allowed to be used in different types of interactions with the user.
static const char* const ALLOWED_EQUATION_INPUT_CHARACTERS = "1234567890-+=xX*^.,eE ";
static const char* const ALLOWED_COEFFICIENT_INPUT_CHARACTERS = "1234567890.-eE";
static const char* const ALLOWED_CONTINUE_INPUT_CHARACTERS = "yYnN";
// Characters that must go with a space character. Otherwise the input is invalid.
static const char* const ALLOWED_AROUND_SPACE_CHARACTERS = "+-=*";
// Characters that divide input string to chunks.
static const char* const DELIMITER = "+-=";

// Max sizes for the different types of input buffers.
/* 
    I know it's cringe, but if you change INPUT_SIZE
    don't forget to fix scanf("%255[^\n]", input)   =)
*/
static const int INPUT_SIZE = 256; 
static const int CHUNK_SIZE = 32;

   
//#define LOG

// Clears the input buffer until a newline character is encountered.
static void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Consume characters from the input buffer.
    }
}


// Removes occurrences of a specified character from the given string.
static void deleteCharacter(char* input, unsigned int* inputLength, const char character)
{
    unsigned int currentEmptySpace = 0;

    // Iterate through the input string.
    for (unsigned int i = 0; i < *inputLength; ++i)
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

    // Add the null terminator to the end of the modified string.
    input[currentEmptySpace] = '\0';
}


// Checks whether the characters in the input string are among the allowed characters.
static bool hasOnlyAllowedCharacters(const char* input, const char* allowedCharacters)
{
    unsigned int allowedCharactersLength = strlen(allowedCharacters); 
    unsigned int inputLength             = strlen(input); 
    // Iterate through the input string.
    for (unsigned int i = 0; i < inputLength; ++i)
    {
        bool isListed = false;

        // Check if the current character is among the allowed characters.
        for (unsigned int j = 0; j < allowedCharactersLength; ++j)
        {
            if (input[i] == allowedCharacters[j])
            {
                isListed = true;
                break;
            }
        }

        // If the current character is not in the allowed list, return false.
        if (!isListed)
        {
            #ifdef LOG
                printf("\t\tLOG: input[%d] = %c\n", i, input[i]);
                printf("\t\tLOG: %c is not among allowed characters\n", input[i]);
            #endif
            return false;
        }
    }

    // If all characters are among the allowed ones, return true.
    return true;
}


// Checks if the given string has the character in it.
static bool hasCharacterInString(const char character, const char input[])
{
    size_t inputLength = strlen(input);
    for (size_t i = 0; i < inputLength; ++i)
	{
        if (character == input[i])
        {
            return true;
        }
    }
    return false;
}


// Returns true if every given character in the string has at least one of the other given characters around.
static bool hasSymbolsAround(const char input[], const char givenCharacter, const char aroundCharacters[])
{
    size_t inputLength = strlen(input);

	for(size_t i = 0; i < inputLength - 1; ++i)
	{
		if(input[i] == givenCharacter)
		{
			// Check if the symbol is to the left.
			bool isToTheLeft = (i >= 1) && hasCharacterInString(input[i - 1], aroundCharacters);

			// Check if the symbol is to the right.
			bool isToTheRight = hasCharacterInString(input[i + 1], aroundCharacters);

			// If it's neither to the left nor to the right...
			if (!(isToTheLeft || isToTheRight))
			{
				return false; // fail.
			}
		}
	}
	return true;
}


// Calculates length of the longest chunk in the given string.
static int lengthOfTheLongestChunk(const char* input)
{
    size_t inputLength  = strlen(input);
	int    chunkSize    = 0;
	int    maxChunkSize = 0;

	// Iterate through the input string.
	for (size_t i = 0; i < inputLength; ++i)
	{
		chunkSize++;

		if (input[i + 1] == '\0' || hasCharacterInString(input[i], DELIMITER)) // If it hits a delimiter...
		{
			if (chunkSize > maxChunkSize)
				maxChunkSize = chunkSize;

			chunkSize = 0; // ...reset the size.
		}
	}
	return maxChunkSize;
}


// This function accepts a string and a character as input. 
// It scans through the string and removes consecutive occurrences of the specified character.
static void deleteRepetitiveCharacters(char input[], const char character)
{
    size_t currentEmptySpace = 0;
    size_t inputLength = strlen(input);

    // Iterate through the input string.
    for (size_t i = 0; i < inputLength; ++i)
    {
        // If the current character is not the character to be deleted...
        if (input[i] != character || input[i + 1] != character)
        {
            // ... move the current character to the position of the current "empty" space and increment it.
            input[currentEmptySpace] = input[i];
            currentEmptySpace++;
        }
    }

    input[currentEmptySpace] = '\0';
}


// Returns `true` if the character can be used to write a number, otherwise `false`.
static bool isNumberCharacter(const char character)
{
    return hasCharacterInString(character, "1234567890.,-=eE");
}


// Check if the given chunk is correct and can be used to set coefficients.
// Takes the chunk from `isEquationInputCorrect()`.
static bool isChunkCorrect(const char chunk[])
{
    size_t chunkLength = sizeof(chunk);
    int        nXsInChunk     = 0; // Number of X in a chunk.
    int     nStarsInChunk     = 0; // Number of * in a chunk.
    int    nCaretsInChunk     = 0; // Number of ^ in a chunk.
    int   nNumbersInChunk     = 0; // Number of different numbers in a chunk.
    bool   passedX        = false; // Checks if we already passed X.

    #ifdef LOG
        printf("\t\tLOG: chunk: <%s>\n", chunk);
    #endif

    // Iterrate through the chunk[].
    for (size_t i = 0; i < chunkLength; i++)
    {
        if (chunk[i] == 'x')
        {
            nXsInChunk++;
            passedX = true;
        }
        else if (chunk[i] == '*')
        {
            nStarsInChunk++;
        }
        else if (chunk[i] == '^')
        {
            nCaretsInChunk++;
            // If ^2 goes without X.
            if ((i != 0 && chunk[i - 1] != 'x') || i == 0)
                return false;
        }
        // If the number is the first character (but not ^2)...
        // or if the number goes after a non-number character (but not ^2)...
        else if ( (isNumberCharacter(chunk[i]) && i == 0                             && chunk[i - 1] != '^')
               || (isNumberCharacter(chunk[i]) && !(isNumberCharacter(chunk[i - 1])) && chunk[i - 1] != '^') )
        {
            nNumbersInChunk++; // ... that's a new number.
            if (passedX) 
            {
                #ifdef LOG
                    printf("\t\tLOG: new number starts with: <%c>\n", chunk[i]);
                #endif

                // If the number (not ^2) goes after the X.
                return false;
            }
        }
        if (nNumbersInChunk > 1 || nCaretsInChunk > 1 || nXsInChunk > 1 || nStarsInChunk > 1)
        {
            return false;
        }
    }
    return true;
}



// Checks if the given string is correct and can be used to set coefficients
static bool isEquationInputCorrect(const char input[])
{
    #ifdef LOG
        printf("\t\tLOG: isEquationInputCorrect started.\n");
    #endif

    char inputBuffer[INPUT_SIZE];
    strcpy(inputBuffer, input); // input[] --> inputBuffer[]

    // Delete multiple spaces. We allow them =)
    deleteRepetitiveCharacters(inputBuffer, ' '); 

    // The first level of "protection".
    if (!hasOnlyAllowedCharacters(inputBuffer, ALLOWED_EQUATION_INPUT_CHARACTERS) // Only has allowed characters.
      || lengthOfTheLongestChunk(inputBuffer) > CHUNK_SIZE                        // Chunks are not too long.
      ||!hasSymbolsAround(inputBuffer, ' ', ALLOWED_AROUND_SPACE_CHARACTERS))     // Spaces are in the right places.
    {
        return false;
    }
    #ifdef LOG
        printf("\t\tLOG: passed hasOnlyAllowedCharacters check!\n");
    #endif
    
    // The second level of "protection".
    // We split inputBuffer[] into chunks[] and pass them to isChunkCorrect().
    char chunkBuffer[CHUNK_SIZE]{};
    int chunkIndex = 0;

    size_t inputBufferLength = sizeof(inputBuffer);
    for (size_t i = 0; i <= inputBufferLength; i++)
    {
        if (hasCharacterInString(inputBuffer[i], DELIMITER) || i == inputBufferLength) // If it hits a delimiter or the end.
        {
            // chunkBuffer[] -> isChunkCorrect()
            chunkBuffer[chunkIndex] = '\0';  
            if (!isChunkCorrect(chunkBuffer))
                return false;

            // Reset chunkBuffer[]
            chunkIndex = 0; 
            chunkBuffer[0] = '\0';
            continue;
        }
        chunkBuffer[chunkIndex] = inputBuffer[i];
        chunkIndex++;
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
static void parseChunkToCoefficient(char* chunk, bool passedEqualSign, Coefficients* coefficients)
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
            chunk[len - 3] = '1'; // Coefficient is equal to '1'.
        }
    }
    // If the chunk ends with x, add to 'b' coefficient.
    else if (len >= 1 && chunk[len - 1] == 'x')
    {
        isB = true;

        // Handle cases like x, +x, -x
        if ((len == 1) || (len == 2 && (chunk[0] == '-' || chunk[0] == '+')))
        {
            chunk[len - 1] = '1'; // Coefficient is equal to '1'.
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
    bool passedEqualSign = false;   // Flag to track whether the equal sign has been encountered.
    int len = strlen(input);        // Length of the input string.
    char chunkBuffer[CHUNK_SIZE]{}; // Temporary buffer to store chunks of the string.
    int chunkCounter = 0;           // Counter for the buffer index.

    // Iterate through the input string
    for (int i = 0; i <= len; i++)
    {
        // If a delimiter is encountered (+, -, =, \0)
        if (input[i] == '\0' || hasCharacterInString(input[i], DELIMITER))
        {
            chunkBuffer[chunkCounter] = '\0'; // Terminate the string in the buffer
            chunkCounter = 0;                 // Reset the counter for the next chunk
            parseChunkToCoefficient(chunkBuffer, passedEqualSign, coefficients); // Process the chunk

            // If the current symbol is the equal sign, set the flag.
            if (input[i] == '=')
            {
                passedEqualSign = true;
                continue; // Skip iteration to prevent equal sign from interfering with processing,
            }
        }

        chunkBuffer[chunkCounter] = input[i]; // Add the character to the buffer
        chunkCounter++;                       // Increment the buffer counter
    }
}


// Prompts the user to input a single coefficient.
static void readCoefficient(double* coef, const char name)
{
    #ifdef LOG 
        printf("\t\tLOG: readCoefficient started.\n");
    #endif

	char   input[INPUT_SIZE]{};        // Buffer to store user's input.
    double validCoefficient   =  0.0 ;
	bool   isValidInput       = false;
    // A loop that keeps prompting the user until valid input is provided.
    while (!isValidInput)
    {
        printf("Please enter coefficient %c: ", name);
        scanf("%255[^\n]", input);    // Read a string from the user's input.
        clearInputBuffer();
		isValidInput = hasOnlyAllowedCharacters(input, ALLOWED_COEFFICIENT_INPUT_CHARACTERS)
                    && strlen(input) < CHUNK_SIZE 
                    && strlen(input) != 0;

        #ifdef LOG
            printf("\t\tLOG: isValidInput = %d.\n", isValidInput);
            printf("\t\tLOG: input[] = '%s'\n", input);
            printf("\t\tLOG: Strlen(input) = %d\n", strlen(input));
        #endif

        if (!isValidInput)
        {
            printf("Invalid input.\n");
        }

    } // Continue the loop as long as the input is invalid.

    validCoefficient = atof(input);
	*coef = validCoefficient; // Set the coefficient.

}


// Prompts the user to input coefficients and sets them in the provided structure.
static void takeCoefficientInput(Coefficients* coefficients)
{
	readCoefficient(&(coefficients->a), 'a');

    readCoefficient(&(coefficients->b), 'b');

    readCoefficient(&(coefficients->c), 'c');
}


// Promts the user to input a valid equation.
static void readEquationInput(char input[])
{
    #ifdef LOG
        printf("\t\tLOG: readEquationInput start.\n");
    #endif

    bool isValidInput = false;
    while (true)
    {
        printf("Enter your equation: ");
        scanf("%255[^\n]", input);
        clearInputBuffer();
        isValidInput = isEquationInputCorrect(input);
        #ifdef LOG
            printf("\t\tLOG: isValidInput = %d.\n", isValidInput);
            printf("\t\tLOG: input[] = %s.\n", input);
        #endif
        if (!isValidInput) // If the input is incorrect...
        {
            printf("Invalid input.\n"); // 
        }
        else
        {
            return;
        }
    }
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


// Promts the user to input and returns a valid input type.
INPUT_TYPE readPreferredInput() {

    char input[INPUT_SIZE];  // Buffer for input
    bool isValidInput = false;

    while (true) {
        // Display the menu of choices
        printf("What type of input would you prefer?\n"
               "(1) Coefficient input\n"
               "(2) Equation input\n");

        // Read the user's input
        scanf("%255[^\n]", input);
        clearInputBuffer();
        isValidInput = hasOnlyAllowedCharacters(input, "12") && strlen(input) == 1;
        char choice = input[0];  // Take the first character

        // Check the user's choice and return the corresponding input type
        if (choice == '1' && isValidInput) {
            return COEFFICIENT_INPUT;
        } else if (choice == '2' && isValidInput) {
            return EQUATION_INPUT;
        } else {
            // Invalid input, inform the user and loop again
            printf("Invalid input. Please choose 1 or 2.\n");
        }
    }
}


// Promts user to enter the equation and sets the corresponding coefficients. 
static void takeEquationInput(Coefficients* coefficients)
{
    char input[INPUT_SIZE];
    readEquationInput(input);
    equationInputToCoefficients(coefficients, input);
}


void readInput(Coefficients* coefficients, int inputType)
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
        assert(0);
		printf("Invalid input type\n"); // Never occurs.
		break;
	}

    // Coefficient a should always be greater than zero!
    if (coefficients->a < 0)
    {
        coefficients->a *= -1.0;
        coefficients->b *= -1.0;
        coefficients->c *= -1.0;
    }
}


bool wantToContinue()
{
    char input[INPUT_SIZE]; 
    while (true) // for (;;)
	{

        printf("Do you want to solve another equation? (y/n): ");
        scanf("%255[^\n]", input);
        clearInputBuffer();
        bool isValidInput = hasOnlyAllowedCharacters(input, ALLOWED_CONTINUE_INPUT_CHARACTERS) && strlen(input) == 1;
        // Check if the input is correct
		if(isValidInput)
		{
			if (input[0] == 'y' || input[0] == 'Y')
            	return true;
			else if (input[0] == 'n' || input[0] == 'N')
				return false;
			else
			{
				// Shouldn't occur
				printf("ERROR. Invalid input. Please enter 'y' or 'n'.\n");
                assert(0);
			}
		}
		else
		{
			printf("Invalid input. Please enter 'y' or 'n'.\n");
		}
    }
}