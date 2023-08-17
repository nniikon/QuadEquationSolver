/*
��������� ������ ��������� �� ������ �������!
������� �����:
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

// ���� �������� � �������, �������� �����, �� ����� �������� =)
#define MAX_INPUT_LENGTH 256
#define MAX_CHUNK_LENGTH 32
#define EPSILON 0.0000001
#define allowedCharacters "1234567890-+=xX*^., "
#define equationInput 1
#define coefficientInput 2

//#define DEBUG // ����� �������

// ��������� � ������������ �������� ��� �����
int askPreferedInput();
// ����������� ����, ������ a, b, c. ���������� ���� ������������� ��-�����������
void takeCoefficientInput(double* a, double* b, double* c);
// ����������� ����, ������ a, b, c. ���������� ���� ������ �������
void takeEquationInput(double* a, double* b, double* c);
// ����������� �����������
void askCoefficient(double* coef, const char name);
// ��������� ������ �� ������������
bool isCorrect(const char* input);
// ��������������� ������, ����� �������� �����
void toDefault(char* input, unsigned int* inputLength);
// ������� ������� �� ������
void deleteCharacter(char* input, unsigned int* inputLength, const char character);
// ����� a, b, c. �������� �� ������������������� �������
void setCoefficients(char* input, double* a, double* b, double* c);
// ������ ������������ �� �������� ������ �����. ������� � setCoefficients
void setChunk(char* chunk, bool passedEqualSign, double* a, double* b, double* c);
// ������� ������� ���������
void formattedCout(double a, double b, double c);
// ������ ���������
void solve(const double a, const double b, const double c);
// ���������� double
bool areSameDouble(double f, double s);


int main()
{
	double a, b, c; // a*x^2 + b*x + c
	int inputType;

	inputType = askPreferedInput();
	// ����������� ���� ������������
	switch(inputType)
	{
	case equationInput:
		takeEquationInput(&a, &b, &c);
		break;
	case coefficientInput:
		takeCoefficientInput(&a, &b, &c);
		break;
	default:
		printf("Invalid input type\n");
		break;
	}

	// ������� �������
	formattedCout(a, b, c);

	// ������
    solve(a, b, c);
}

int askPreferedInput()
{
	// ���������� � ������������ �������� ��� �����
	printf("%s%s%s", "What type of input would you prefer?\n",
			"(1) Coefficient input\n",
			"(2) Equation input\n");
	char choice = getchar();
	if(choice == '1')
		return coefficientInput;
	else if(choice == '2')
		return equationInput;
	else
	{
		printf("Invalid input. But I really like the second option, so I chose it for you =\)\n");
		return equationInput;
	}
}


void takeEquationInput(double* a, double* b, double* c)
{

	// ������ �����
	while(getchar() != '\n');

	// �������� ������, � ������� ����� ��������� ���� ������������
	char input[MAX_INPUT_LENGTH];
	do
	{
		// ����������� ����
		printf("Enter your equation: ");
		scanf("%[^\n]", input);
		// ��������� ������������ �����
		if (!isCorrect(input))
		{
			printf("Invalid input.\n"); // ������ ������������
			input[0] = '\n'; // "�������" ������
			while (getchar() != '\n'); // ������� �����
		}
	} while (!isCorrect(input));

    unsigned int inputLength = strlen(input); // ����� ������

	// �������� � ������������ ����
	toDefault(input, &inputLength);

	// ������� ������������
	setCoefficients(input, a, b, c);

	#ifdef DEBUG
		printf("\nDEBUG: standartised equation: %s\n", input);
        printf("DEBUG: a = %f \nDEBUG: b = %f \nDEBUG: c = %f\n\n", a, b, c);
    #endif

}

bool isCorrect(const char* input)
{
    bool isListed;

    // �������� �� ������� ������� �� ������� ������.
    for(unsigned int i = 0; i < strlen(input); i++)
    {
        isListed = false;

        // ���������, ������������ �� ������� ������ ����� ����������� ��������.
        for(unsigned int j = 0; j < strlen(allowedCharacters); j++)
        {
            if(input[i] == allowedCharacters[j])
            {
                isListed = true;
                break;
            }
        }

        // ���� ������� ������ �� ������ ����� �����������, ���������� false.
        if(!isListed)
            return false;
    }

    // ���� ��� ������� ������ ��������, ���������� true.
    return true;
}

void deleteCharacter(char* input, unsigned int* inputLength, const char character)
{
	// ���������� ��� ������������ ������� �������, �� ������� ����� ��������� ��������� ������.
	int currentEmptySpace = 0;

	// ���������� �� ���� �������� ������.
	for(unsigned int i = 0; i < *inputLength; i++)
	{
		// ���� ������� ������ �� ��������� � ��������, ������� ����� �������...
		if(input[i] != character)
		{
			// ��������� ������� ������ �� ������� �������� "�������" ����� � ����������� ���.
			input[currentEmptySpace] = input[i];
			currentEmptySpace++;
		}
	}

	// ��������� ����� ������ ����� �������� ��������.
	*inputLength = currentEmptySpace;

	// ��������� ����������� ������� ������, ����� ������ ���������� ����������.
	input[currentEmptySpace] = '\0';
}

void toDefault(char* input, unsigned int* inputLength)
{
	/*
	����������� ������ ������ ��������� �������� ���:

	5x^2-6x+12=5x-12x^2

	*/
	// ������� �������������� �������
	deleteCharacter(input, inputLength, ' ');
	deleteCharacter(input, inputLength, '*');

	// ��������������� ������� �����
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
		}
	}

}

void setChunk(char* chunk, bool passedEqualSign, double* a, double* b, double* c)
{
	/*
	��� ������� ��������� ����� ������ ����� � ������ � ��� ������� ������������
	������� �����:
	+5x^2
	-3.4x
	x
	+5.3
	*/

	bool isA = false,
		 isB = false,
		 isC = false;
	double value = 0.0;
	unsigned len = strlen(chunk);

	//

	// ���������, � ������ ������������ �� ����� ���������� value

	// ���� ������ ������������� �� x^2, �� ���������� � �
	if (len >= 3 && chunk[len - 3] == 'x' && chunk[len - 2] == '^' && chunk[len - 1] == '2')
	{
		isA = true;

		// ���������� ������ x^2, +x^2, -x^2
		if( (len == 3) || (len == 4 && (chunk[0] == '-' || chunk[0] == '+')) )
		{
			// ����� ������ x ������ ��������� ��������, ������� ���� �� ����� ������
			chunk[len - 3] = '1';
		}
	}
	// ���� ������ ������������� �� x, �� ���������� � b
	else if (len >= 1 && chunk[len - 1] == 'x')
	{
		isB = true;

		// ���������� ������ x, +�, -�
		if( (len == 1) || (len == 2 && (chunk[0] == '-' || chunk[0] == '+')) )
		{
			// ����� ������ x ������ ��������� ��������, ������� ���� �� ����� ������
			chunk[len - 1] = '1';
		}
	}
	// � ����� ������ ������, ��� ������ �����, ���������� � c
	else
	{
		isC = true;
	}

	// ������� value
	value = atof(chunk);

	// ���� �� �� ������ ������� ���������, �� ��������� ����� (� �������)
	if (passedEqualSign)
	{
		value = -value;
	}

	// �� � ���������� value � �������������
	if(isA)
	{
		*a += value;
		return;
	}
	if(isB)
	{
		*b += value;
		return;
	}
	if(isC)
	{
		*c += value;
		return;
	}
}

void setCoefficients(char* input, double* a, double* b, double* c)
{
    bool passedEqualSign = false;  // ���� ��� ������������, ������ �� ���� ���������
    int len = strlen(input);        // ����� ������� ������
    char strChunk[MAX_CHUNK_LENGTH]{};  // ��������� ����� ��� �������� ������ ������
    int chunkCounter = 0;           // ������� ��� ������� ������

    // ��������� �� �������� ������
    for (int i = 0; i <= len; i++)
    {
        // ���� ����� �� ������������ ����� (+, -, =, \0)
        if (input[i] == '+' || input[i] == '-' || input[i] == '=' || input[i] == '\0')
        {
            strChunk[chunkCounter] = '\0';  // ��������� ������ � ������
            chunkCounter = 0;  // ���������� ������� ��� ���������� �����
            setChunk(strChunk, passedEqualSign, a, b, c);  // ������������ �����

            // ���� ������� ���� - ���������, ������������� ����
            if (input[i] == '=')
            {
                passedEqualSign = true;
                continue; // ��������� ��������, ����� ����� �� �������� ���������
            }
        }

        strChunk[chunkCounter] = input[i];  // ��������� ������ � �����
        chunkCounter++;  // ����������� ������� ������
    }
}


void formattedCout(const double a, const double b, const double c)
{
	// ������ ������� ������� ���������, ������ �����������
	if (areSameDouble(a, 0.0) && areSameDouble(b, 0.0))
	{
		if (areSameDouble(c, 0.0))
			printf("0 == 0\n");
		else
			printf("%g != 0\n", c);
		return;
	}

    if (!areSameDouble(a, 0.0))
	{
        if (areSameDouble(a, -1.0))
            printf("-x^2 ");
        else if (areSameDouble(a, 1.0))
            printf("x^2 ");
        else
            printf("%gx^2 ", a);
    }

    if (!areSameDouble(b, 0.0))
	{
        if (b < 0)
            printf("- ");
        else if (!areSameDouble(a, 0.0))
            printf("+ ");

        if (areSameDouble(b, -1.0))
            printf("x ");
        else if (areSameDouble(b, 1.0))
            printf("x ");
        else
            printf("%gx ", fabs(b));
    }

    if (!areSameDouble(c, 0.0))
    {
        if (c < 0)
            printf("- %g ", -c);
        else if (!areSameDouble(b, 0.0))
            printf("+ %g ", c);
        else
            printf("%g ", c);
    }
	printf("= 0\n");

}

bool areSameDouble(double f, double s)
{
	return fabs(f - s) < EPSILON; // ����
}

void solve(const double a, const double b, const double c)
{
	if(!areSameDouble(a, 0.0)) // ���������� ���������
	{
		double d = b * b - 4 * a * c; // ������������!
		if(d > 0)
		{
			printf("Two real solutions were found!\n");
			printf("x1 = %g\n", (-b + sqrt(d))/(2.0*a) );
			printf("x2 = %g\n", (-b - sqrt(d))/(2.0*a) );
		}
		else if(areSameDouble(d, 0.0)) // � ��� ��� ��� ��������� ����������
		{
			printf("Only one real solution was found!\n");
			printf("x = %g\n", -b / (2.0 * a));
		}
		else
		{
			printf("No real solutions were found =(\n");
		}
	}
	else if(!areSameDouble(b, 0.0)) // �������� ���������
	{
		printf("Only one real solution was found\n");
		printf("x = %g\n", -(c / b));
	}
	else
	{
		if(areSameDouble(c, 0.0))
		{
			printf("Rare ending unlocked,\nAn infinite number of solutions were found!\n");
		}
		else
		{
			printf("No solutions were found =(\n");
		}
	}
}

void askCoefficient(double* coef, const char name)
{
	int validInput = 0;
	do
	{
		// ������ ������ �����������
		printf("Please enter coefficient %c: ", name);
		validInput = scanf("%lf", coef);
		#ifdef DEBUG
			printf("validInput: %d\nNumber %c = %f\n", validInput, name ,*coef);
		#endif
		// ���� scanf ���������� 0
		if (validInput == 0)
		{
			// ������ �����
			printf("Invalid input.\n");
			// ������� ����� (��� ����� �� ��������)
			while (getchar() != '\n');
		}
	} while (validInput == 0);
	// ������ �����
	while (getchar() != '\n');
}

void takeCoefficientInput(double* a, double* b, double* c)
{

	// ������ �����
	while(getchar() != '\n');

	askCoefficient(a, 'a');
	askCoefficient(b, 'b');
	askCoefficient(c, 'c');
}
