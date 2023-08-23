#include "test.h"


static void testInput(char input[], char givenCharacter, char aroundCharacters[], bool expectedOutput)
{
	
}


void testInput()
{
	char givenCharacter = ' ';
	char aroundCharacters[100] = "+-*=";
	char input1[100] = "123 234";
	testInput_hasSymbolsAround(input1, givenCharacter, aroundCharacters, false);
	char input2[100] = "x^2 - 5x + 12 = 0";
	testInput_hasSymbolsAround(input2, givenCharacter, aroundCharacters, true);
	char input3[100] = "x^2 - 5x + 12 = x - 15 ";
	testInput_hasSymbolsAround(input3, givenCharacter, aroundCharacters, true);
	char input4[100] = "x^2 - 5x + 12 = x - 15 20";
	testInput_hasSymbolsAround(input4, givenCharacter, aroundCharacters, false);
}

