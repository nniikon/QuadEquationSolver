#include "../include/readInput.h"
#include <string.h>

//#define LOG

// Deletes spaces at the beggining and at the end of the string.
static void deleteMeaninglessSpaces(char input[])
{
    //assert(strlen(input) > 1);
    assert(input);
    size_t inputLength = strlen(input);
    size_t newStart = 0;
    int newEnd = int(inputLength) - 1;
    #ifdef LOG
        printf("deleteMeaninglessSpaces() started");
    #endif
    // Find the first non-space character.
    while (newStart < inputLength && input[newStart] == ' ')
    {
        newStart++;
    }

    // Find the last non-space character.
    while (newEnd > 0 && (input[newEnd] == ' ' || input[newEnd] == '\n'))
    {
        newEnd--;
    }
    size_t newLength = newEnd - newStart;

    #ifdef LOG
        printf("newStart = %d\nnewEnd = %d\nnewLength = %d\n", newStart, newEnd, newLength);
    #endif

    // Rewrite input[] without the spaces.
    for (size_t i = 0; i <= newLength; i++)
    {
        input[i] = input[i + newStart];
    }

    // End the string with '\0'.
    input[newLength + 1] = '\0';
}


static void readRawInput(char input[], const size_t size)
{
    // Read the input.
    fgets(input, size, stdin);

    deleteMeaninglessSpaces(input);

    // Replace the newline character with null-terminator.
    size_t length = strlen(input);
    if (length > 0 && input[length - 1] == '\n') 
        input[length - 1] = '\0'; 
}


void readInput(const char greetingString[], const char invalidString[], bool (*isValidInput)(const char []), char input[], size_t size)
{
    #ifdef LOG
        printf("Started readInput().\n");
    #endif

    bool isValid = false;
    printf("%s", greetingString);

    while (!isValid)
    {
        readRawInput(input, size);
        
        isValid = isValidInput(input);

        if (!isValid)
        {
            printf("%s", invalidString);
        }
    }
}
