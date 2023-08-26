#ifndef READINPUT_H
#define READINPUT_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Prompt the user with the given message until they provide valid input as determined by the provided validation function.
 * 
 * This function repeatedly displays the greeting message to the user and waits for their input. 
 * The provided validation function is used to determine if the input is valid or not. 
 * If the input is invalid, the user is informed using the provided invalid input message.
 * 
 * @param [in]  greetingString A message that informs the user about the expected input.
 * @param [in]  invalidString  A message that is displayed when the user's input is invalid.
 * @param [in]  isValidInput   A pointer to a function responsible for checking input validity.
 * @param [in]  size           The size of the input buffer.
 * @param [out] input          A string where the valid input will be stored.
 */
void readInput(const char greetingString[], const char invalidString[], bool (*isValidInput)(const char []), char input[], size_t size);

#endif