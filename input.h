#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "consts.h"
// Prompts the user to select their preferred input type.
int askPreferredInput();
// Prompts the user to input coefficients based on the input type
void takeInput(Coefficients* coefficients, int inputType);
// Askes the user if they want to continue
bool wantToContinue();


