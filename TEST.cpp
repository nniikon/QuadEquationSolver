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
#define MAX_INPUT_LENGTH 256
#define MAX_NUMBER_LENGTH 32
#define EPSILON 0.0000001 // ���� �������� � �������, �������� �����, �� ����� �������� =)

//#define DEBUG // ����� �������

double a, b, c; // a*x^2 + b*x + c

// ����������� ����, ������ a, b, c
void takeInput();
// ������� �������, �������� ������� �� ����� � �.�.(��������������� ������, ����� �������� �����)
void toDefault(char* input, unsigned int* inputLength);
// ����� a, b, c. �������� �� ������������������� �������
void setCoefficients(char* input, unsigned int inputLength);
// ������� ������� ���� ������� ��� �������� ����
void formattedCout();
// ������ ���������
void solve();
// ���������� double (����)
bool areSameDouble(double f, double s);

void takeInput()
{
	char input[MAX_INPUT_LENGTH];
	printf("Enter your equation: ");
	scanf("%[^\n]", input); // � ��� ��������, scanf ��������������� ������ �� \n
    unsigned int inputLength = strlen(input); // ����� ������
	// �������� � ������������ ����
	toDefault(input, &inputLength);
	// ������� ������������
	setCoefficients(input, inputLength);
	// ������� ������� =)
	formattedCout();
	#ifdef DEBUG
		printf("\nDEBUG: standartised equation: %s\n", input);
        printf("DEBUG: a = %f \nDEBUG: b = %f \nDEBUG: c = %f\n\n", a, b, c);
    #endif

}

void toDefault(char* input, unsigned int* inputLength)
{
	for(unsigned int i = 0; i < *inputLength; i++)
	{
		if(input[i] == ' ' || input[i] == '*') // ���� ������� �������� ������
		{
			for(unsigned int j = i; j < *inputLength; j++)
			{
				input[j] = input[j + 1]; // �������� ��� ������ �����, ����� ��� ������
			}
			input[*inputLength] = '\0'; // � ����� ������� ����� ������ � � �����
			(*inputLength)--;
		}
		else if(input[i] == ',')
		{
			input[i] = '.';
		}
		else if(input[i] == 'X')
		{
			input[i] = 'x';
		}
		if(input[i] == '=')
		{
			input[i] = ' '; // ������� "=" �� " ", ��� ����� ������� �����
		}
	}
}
void setCoefficients(char* input, unsigned int inputLength)
{
	// ���������, ����� ����� ����� ��� ������������ ����� ���������� �� -1.0
	float passedEqualSign = 1.0f;
	// �� ������� ������ ����� �� �����, ������ �� ������� ����� ��������� �����
	char strNumber[MAX_NUMBER_LENGTH]{};
	// ������� ������������
	for(unsigned int i = 0; i <= inputLength; i++)
	{
		if(input[i] == '+' || input[i] == '-' || input[i] == '\0' || input[i] == ' ')
		{
			// ����� �� ������������, strNumber �������� �������� ���: "-5.2x^2" ��� "+7.23x"
			if(strNumber[i - 2] == '^') // ���� ������������� �� x^2 (a)
			{
				strNumber[i - 3] = '\0'; // ������ x ���������� \0. � ������ ������� ������ �����
				a += atof(strNumber) * passedEqualSign;
				if(strNumber[i - 4] == '+' || i == 3 || strNumber[i - 4] == ' ')
					// ���� ����� x ��� ������������, �� ��� +- 1
				{
					a += 1 * passedEqualSign;
				}
				if(strNumber[i - 4] == '-') // ���� ����� � �����
				{
					a -= 1 * passedEqualSign;
				}
			}
			else if(strNumber[i - 1] == 'x') // ���� ������������� �� x (b)
			{
				strNumber[i - 1] = '\0'; // �������� ��� \0. � ������ ������� ������ �����
				b += atof(strNumber) * passedEqualSign;
				if(strNumber[i - 2] == '+' || i == 1 || strNumber[i - 2] == ' ')
					// ���� ����� x ��� ������������, �� ��� +- 1
				{
					b += 1 * passedEqualSign;
				}
				if(strNumber[i - 2] == '-') // ���� ����� � �����
				{
					b -= 1 * passedEqualSign;
				}
			}
			else // ���� ��� ������ �����
			{
				strNumber[i] = '\0';
				c += atof(strNumber) * passedEqualSign;
			}
			for(unsigned int j = 0; j < i; j++)
			{
				strNumber[j] = ' '; // ��������, ����� ����� ������ �� ������
			}

		}

		strNumber[i] = input[i]; // �������� ������� �� input � strNumber, ���� �� ������ �� +- ��� ' '

		if(input[i] == ' ') // ��� ���� ���������, ������
		{
			passedEqualSign = -1.0f;
			// ���� �� ������ ���� ���������, �� ������ ����, ��� � 7 ������ �����
		}
	}
}

void formattedCout()
{
	// ���������� ���������� �������������� �� ��� �������
	// �� ��� ����� ���� ������� ������� ���������
	// ���� ���-�� ������ �� ��� ��� ���� ������� ������ ������ ��� ���-�� ����� ����
	// � ����� ������ � �� ������������ (���� ������ ��, ��� ����������)
	if (a == 0.0 && b == 0.0 && c == 0.0)
	{
		printf("0 = 0\n");
		return;
	}
	if (a == 0.0 && b == 0.0 && c != 0.0)
	{
		printf("%g != 0\n", c);
		return;
	}
	if (a ==  1.0)
	{
		printf("x^2 ");
	}
	else if(a == -1.0)
	{
		printf("-x^2 ");
	}
	else if (a != 0.0)
	{
		printf("%gx^2 ", a);
	}
	// ��� ������������)0)
	if (a != 0)
	{
		if (b ==  1.0)
		{
			printf("+ x ");
		}
		else if(b == -1.0)
		{
			printf("- x ");
		}
		else if(b > 0.0)
		{
			printf("+ %gx ", b);
		}
		else if(b < 0.0)
		{
			printf("- %gx ", -b);
		}
	}
	else
	{
		if (b ==  1.0)
		{
			printf("x ");
		}
		else if(b == -1.0)
		{
			printf("-x ");
		}
		else if(b > 0.0)
		{
			printf("%gx ", b);
		}
		else if(b < 0.0)
		{
			printf("-%gx ", -b);
		}
	}
	//
	if(c > 0.0)
	{
		printf("+ %g ", c);
	}
	else if(c < 0.0)
	{
		printf("- %g ", -c);
	}
	printf("= 0\n");
}

bool areSameDouble(double f, double s)
{
	return fabs(f - s) < EPSILON; // ����
}

void solve()
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
int main()
{
    takeInput();
    solve();
}
