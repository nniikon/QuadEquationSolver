#pragma once
#include "equationParams.h"
#include "doubleOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Characters that are allowed to be used in different types of interactions with the user.
const char* const ALLOWED_EQUATION_INPUT_CHARACTERS = "1234567890-+=xX*^., ";
const char* const ALLOWED_COEFFICIENT_INPUT_CHARACTERS = "1234567890.-";
const char* const ALLOWED_CONTINUE_INPUT_CHARACTERS = "yYnN";
// Characters that must go with a space character. Otherwise the input is invalid.
const char* const ALLOWED_AROUND_SPACE_CHARACTERS = "+-=*";
// Characters that can't go with a 'x' character.  Otherwise the input is invalid.
const char* const RESTRICTED_AROUND_X_CHARACTERS = "xX";
// Characters that divide input string to chunks.
const char* const DELIMITER = "+-=";
// Max sizes for the different types of input buffers.
const int MAX_INPUT_LENGTH = 512;
const int MAX_CHUNK_LENGTH = 32;
// Input types
enum INPUT_TYPE{COEFFICIENT_INPUT, EQUATION_INPUT};


// Prompts the user to select their preferred input type.
int askPreferredInput();
// Prompts the user to input coefficients based on the input type.
void takeInput(Coefficients* coefficients, int inputType);
// Askes the user if they want to continue.
bool wantToContinue();
// Sets the coefficients in the provided structure based on the provided input.
void setEquationInput(Coefficients* coefficients, char input[]);
// Tests equation input
void testEquationInput();

// TODO: add comments to the .cpp file
