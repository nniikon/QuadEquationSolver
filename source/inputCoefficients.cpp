#include "../include/inputCoefficients.h"

// Characters that are allowed to be used in different types of interactions with the user.
static const char* const ALLOWED_EQUATION_INPUT_CHARACTERS    = "1234567890-+=xX*^.,eE ";
static const char* const ALLOWED_COEFFICIENT_INPUT_CHARACTERS = "1234567890.-eE";
static const char* const ALLOWED_CONTINUE_INPUT_CHARACTERS    = "yYnN";

// Characters that must go with a space character. Otherwise the input is invalid.
static const char* const ALLOWED_AROUND_SPACE_CHARACTERS = "+-=*";

// Characters that divide input string to chunks.
static const char* const DELIMITER = "+-=";

// Max sizes for the different types of input buffers.
static const int INPUT_SIZE = 256;
static const int CHUNK_SIZE = 32;


#define LOG



/*
   +-------------------------+
   | MISCELLANEOUS FUNCTIONS |
   +-------------------------+
*/

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
    // Iterate through the input string.
    for (unsigned int i = 0; input[i] != '\0'; ++i)
    {
        bool isListed = false;

        // Check if the current character is among the allowed characters.
        for (unsigned int j = 0; allowedCharacters[j] != '\0'; ++j)
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
    for (size_t i = 0; input[i] != '\0'; ++i) // <<<---------------+
	{                                         //                   |
        if (character == input[i])            //                   |
        {                                     //                   |
            return true; // TODO fix      >>>----------------------+
        }                // DO NOT TOUCH
    }                    // DED COMMENTS

    return false;
}


// Returns true if every given character in the string has at least one of the other given characters around.
static bool hasSymbolsAround(const char input[], const char givenCharacter, const char aroundCharacters[])
{
	for (size_t i = 0; input[i + 1] != '\0'; ++i)
	{
		if (input[i] == givenCharacter)
		{
			// Check if the symbol is to the left.
			bool isToTheLeft = (i >= 1) && hasCharacterInString(input[i - 1], aroundCharacters);

			// Check if the symbol is to the right.
			bool isToTheRight =            hasCharacterInString(input[i + 1], aroundCharacters);

			// If it's neither to the left nor to the right...
			if (!(isToTheLeft || isToTheRight))
			{
				return false; // fail.
			}
		}
	}

	return true;
}


// This function accepts a string and a character as input. 
// It scans through the string and removes consecutive occurrences of the specified character.
static void deleteRepetitiveCharacters(char input[], const char character)
{
    size_t currentEmptySpace = 0;

    // Iterate through the input string.
    for (size_t i = 0; input[i] != '\0'; ++i)
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


// Processes the input string, preparing it for use with the setCoefficients_equationInput() function.
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
            case 'X': input[i] = 'x'; break;
            case ',': input[i] = '.'; break;
            default: /* do nothing */ break;
        }
    }
}


// Returns `true` if the character can be used to write a number, otherwise `false`.
static bool isNumberCharacter(const char character)
{
    return hasCharacterInString(character, "1234567890.,-=eE");
}





/*
   +----------------------------+
   | VALIDATING INPUT FUNCTIONS |
   +----------------------------+
*/

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

    if (chunkLength > CHUNK_SIZE)
        return false;

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
        else if ( (isNumberCharacter(chunk[i]) &&              i == 0                && chunk[i - 1] != '^')
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


// Checks if the given string is correct and can be used to set coefficients.
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
    if (!hasOnlyAllowedCharacters(inputBuffer,      ALLOWED_EQUATION_INPUT_CHARACTERS) // Only has allowed characters.
      ||!hasSymbolsAround        (inputBuffer, ' ', ALLOWED_AROUND_SPACE_CHARACTERS))  // Spaces are in the right places.
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


    for (size_t i = 0; inputBuffer[i + 1] != '\0'; i++)
    {
        if (hasCharacterInString(inputBuffer[i], DELIMITER) || inputBuffer[i] == '\0') // If it hits a delimiter or the end.
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


static bool isCoefficientInputCorrect(const char input[])
{
    return hasOnlyAllowedCharacters(input, ALLOWED_COEFFICIENT_INPUT_CHARACTERS)
        && strlen(input) < CHUNK_SIZE 
        && strlen(input) != 0;
}


static bool isWantToContinueInputCorrect(const char input[])
{
    return hasOnlyAllowedCharacters(input, ALLOWED_CONTINUE_INPUT_CHARACTERS) 
        && strlen(input) == 1;
}


static bool isPreferredInputCorrect(const char input[])
{
    return hasOnlyAllowedCharacters(input, "12") 
        && strlen(input) == 1;
}





/*
   +---------------------------+
   | SET_COEFFICIENT FUNCTIONS |
   +---------------------------+
*/

// Works with setCoefficients_equationInput.
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
static void setCoefficients_equationInput(char* input, Coefficients* coefficients)
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
static void setSingleCoefficient_coefficientInput(double* coef, const char name)
{
    #define ASK_USER "Please enter coefficient "

    char input[INPUT_SIZE]{};
    char greetingString[] = ASK_USER "x: ";

    // Set up the correct greetingString[].
    sprintf(greetingString, ASK_USER "%c: ", name);
    char invalidString[] = "Invalid input. Try again: ";

    readInput(greetingString, invalidString, &isCoefficientInputCorrect, input, INPUT_SIZE);

	*coef = atof(input);; // Set the coefficient.

    #undef ASK_USER
}


// Prompts the user to input coefficients and sets them in the provided structure.
static void setCoefficients_coefficientInput(Coefficients* coefficients)
{
	setSingleCoefficient_coefficientInput(&(coefficients->a), 'a');

    setSingleCoefficient_coefficientInput(&(coefficients->b), 'b');

    setSingleCoefficient_coefficientInput(&(coefficients->c), 'c');
}


// Sets coefficients, takes a correct string as input.
void setCoefficients_stringInput(Coefficients* coefficients, char input[])
{
    unsigned int inputLength = strlen(input);

    // Prepare the equation input.
    normalizeEquationInput(input, &inputLength);

    // Set the coefficients
    setCoefficients_equationInput(input, coefficients);
}


// Promts user to enter the equation and sets the corresponding coefficients. 
static void setCoefficients_equationInput(Coefficients* coefficients)
{
    char input[INPUT_SIZE];
    char greetingString[] = "Please enter your equation: ";
    char  invalidString[] = "Invalid input. Try again: ";
    readInput(greetingString, invalidString, &isEquationInputCorrect, input, INPUT_SIZE);
    setCoefficients_stringInput(coefficients, input);
}


void setCoefficients(Coefficients* coefficients, int inputType)
{
	switch(inputType)
	{
	case EQUATION_INPUT:
		setCoefficients_equationInput(coefficients);
		break;
	case COEFFICIENT_INPUT:
		setCoefficients_coefficientInput(coefficients);
		break;
	default:
        assert(0);
		break;
	}
}





/*
   +----------------------------+
   | USER INTERACTION FUNCTIONS |
   +----------------------------+
*/

bool wantToContinue()
{
    char input[INPUT_SIZE]; 
    char greetingString[] = "Do you want to solve another equation? (y/n): ";
    char  invalidString[] = "Invalid input. Please enter 'y' or 'n': ";

    readInput(greetingString, invalidString, &isWantToContinueInputCorrect, input, INPUT_SIZE);

	if (input[0] == 'y' || input[0] == 'Y')
        return true;
	else if (input[0] == 'n' || input[0] == 'N')
		return false;
	else
        assert(0);
}


// Promts the user to input and returns a valid input type.
InputType getPreferredInput() 
{
    char input[INPUT_SIZE];  // Buffer for input

    char greetingString[] = "What type of input would you prefer?\n"
                            "(1) Coefficient input\n"
                            "(2) Equation input\n";
    char invalidString[]  = "Invalid input. Please choose 1 or 2: ";

    readInput(greetingString, invalidString, &isPreferredInputCorrect, input, INPUT_SIZE);


    // Check the user's choice and return the corresponding input type
    if (input[0] == '1') 
    {
        return COEFFICIENT_INPUT;
    } 
    else if (input[0] == '2') 
    {
        return EQUATION_INPUT;
    }
    else
    {
        assert(0);
    }

}