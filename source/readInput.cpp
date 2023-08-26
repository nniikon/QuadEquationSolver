#include "../include/readInput.h"
#include <string.h>

void readInput(const char greetingString[], const char invalidString[], bool (*isValidInput)(const char []), char input[], size_t size)
{
    bool isValid = false;
    printf("%s", greetingString);
    while (!isValid)
    {
        // Read the input.
        fgets(input, size, stdin);

        // Replace the newline character with null-terminator.
        size_t length = strlen(input);
        if (length > 0 && input[length - 1] == '\n') 
            input[length - 1] = '\0'; 
        
        isValid = isValidInput(input);

        if (!isValid)
        {
            printf("%s", invalidString);
        }
    }
    
}