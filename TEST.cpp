/*
Программа решает уравнение до второй степени!
Примеры ввода:
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

// взял значения с потолка, наверное плохо, но вроде работает =)
#define MAX_INPUT_LENGTH 256
#define MAX_NUMBER_LENGTH 32
#define EPSILON 0.0000001
/*
isEquationInput true - ввод целой строки
isEquationInput false - ввод коэффициентов по-отдельности
*/
#define isEquationInput false

//#define DEBUG // режим отладки

double a, b, c; // a*x^2 + b*x + c

// Запрашивает ввод, задает a, b, c. Использует ввод коэффициентов по-отдельности
void takeCoefficientInput();
// Запрашивает ввод, задает a, b, c. Использует ввод строки целиком
void takeEquationInput();
// Запрашивает коэффициент
void askCoefficient(double* coef, const char name);
// Убирает пробелы, заменяет запятые на точки и т.д.(стандартизирует строку, может поменять длину)
void toDefault(char* input, unsigned int* inputLength);
// Задаёт a, b, c. Работает со стандартизированной строкой
void setCoefficients(char* input, unsigned int inputLength);
// Красиво выводит хлам который мог написать юзер
void formattedCout();
// Решает уравнение
void solve();
// Сравниваем double (типо)
bool areSameDouble(double f, double s);

void takeEquationInput()
{
	char input[MAX_INPUT_LENGTH];
	printf("Enter your equation: ");
	scanf("%[^\n]", input); // я это нагуглил, scanf останавливается только на \n
    unsigned int inputLength = strlen(input); // длина строки
	// Приведем к стандартному виду
	toDefault(input, &inputLength);
	// Зададим коэффициенты
	#ifdef DEBUG
		printf("\nDEBUG: toDefault done\n");
    #endif
	setCoefficients(input, inputLength);
	#ifdef DEBUG
		printf("\nDEBUG: setCoefficients done\n");
    #endif
	// Красиво выводим =)
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
		if(input[i] == ' ' || input[i] == '*') // Если находим ненужный символ
		{
			for(unsigned int j = i; j < *inputLength; j++)
			{
				input[j] = input[j + 1]; // Сдвигаем всю строку влево, чтобы его убрать
			}
			input[*inputLength] = '\0'; // А также двигаем конец строки и её длину
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
			input[i] = ' '; // Заменим "=" на " ", это будет полезно позже
		}
	}
}
void setCoefficients(char* input, unsigned int inputLength)
{
	// Множитель, после знака равно все коэффициенты будут умножаться на -1.0
	float passedEqualSign = 1.0f;
	// Мы поделим строку ввода на части, каждая из которых будет храниться здесь
	char strNumber[MAX_NUMBER_LENGTH]{};
	// Находим коэффициенты
	for(unsigned int i = 0; i <= inputLength; i++)
	{
		if(input[i] == '+' || input[i] == '-' || input[i] == '\0' || input[i] == ' ')
		{
			// Дошли до ограничителя, strNumber выглядит примерно так: "-5.2x^2" или "+7.23x"
			if(i >= 3 && strNumber[i - 2] == '^') // Если заканчивается на x^2 (a)
			{
				strNumber[i - 3] = '\0'; // Вместо x записываем \0. В строке остаётся только число
				a += atof(strNumber) * passedEqualSign;
				if(i == 3 || strNumber[i - 4] == '+' || strNumber[i - 4] == ' ')
					// Если перед x нет коэффициента, то это +- 1
				{
					a += 1 * passedEqualSign;
				}
				if(i != 3 && strNumber[i - 4] == '-') // Если перед х минус
				{
					a -= 1 * passedEqualSign;
				}
			}
			else if(strNumber[i - 1] == 'x') // Если заканчивается на x (b)
			{
				strNumber[i - 1] = '\0'; // Заменяем его \0. В строке остаётся только число
				b += atof(strNumber) * passedEqualSign;
				if(i == 1 || strNumber[i - 2] == '+' || strNumber[i - 2] == ' ')
					// Если перед x нет коэффициента, то это +- 1
				{
					b += 1 * passedEqualSign;
				}
				if(i != 1 && strNumber[i - 2] == '-') // Если перед х минус
				{
					b -= 1 * passedEqualSign;
				}
			}
			else // Если это просто число
			{
				strNumber[i] = '\0';
				c += atof(strNumber) * passedEqualSign;
			}
			for(unsigned int j = 0; j < i; j++)
			{
				strNumber[j] = ' '; // Зачищаем, чтобы потом ничего не мешало
			}

		}

		strNumber[i] = input[i]; // Копируем символы из input в strNumber, пока не дойдем до +- или ' '

		if(input[i] == ' ') // это знак равенства, честно
		{
			passedEqualSign = -1.0f;
			// Если мы прошли знак равенства, то меняем знак, как в 7 классе учили
		}
	}
}

void formattedCout()
{
	// Компилятор выкидывает предупреждение на эту функцию
	// Но она всего лишь красиво выводит уравнение
	// Если что-то пойдет не так это лишь добавит лишний пробел или что-то вроде того
	// Я решил забить и не переписывать (хотя стоило бы, она громоздкая)
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
	// без комментариев)0)
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
	return fabs(f - s) < EPSILON; // база
}

void solve()
{
	if(!areSameDouble(a, 0.0)) // квадратное уравнение
	{
		double d = b * b - 4 * a * c; // Дискриминант!
		if(d > 0)
		{
			printf("Two real solutions were found!\n");
			printf("x1 = %g\n", (-b + sqrt(d))/(2.0*a) );
			printf("x2 = %g\n", (-b - sqrt(d))/(2.0*a) );
		}
		else if(areSameDouble(d, 0.0)) // а вот тут уже нормально сравниваем
		{
			printf("Only one real solution was found!\n");
			printf("x = %g\n", -b / (2.0 * a));
		}
		else
		{
			printf("No real solutions were found =(\n");
		}
	}
	else if(!areSameDouble(b, 0.0)) // линейное уравнение
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
		// Просим ввести коэффициент
		printf("Please enter a coefficient %c: ", name);
		#ifdef DEBUG
			printf("validInput: %d\nNumber %c = %f\n", validInput, name ,*coef);
		#endif
		validInput = scanf("%lf", coef);
		// Если scanf возвращает 0
		if (validInput == 0)
		{
			// Ругаем юзера
			printf("Invalid input.\n");
			// Очищаем буфер (без этого не работает)
			while (getchar() != '\n');
		}
	} while (validInput == 0);
	// Чистим буфер
	while (getchar() != '\n');
}

void takeCoefficientInput()
{
	askCoefficient(&a, 'a');
	askCoefficient(&b, 'b');
	askCoefficient(&c, 'c');
	// Красиво выводим =)
	formattedCout();
}


int main()
{
	if(isEquationInput)
	{
		takeEquationInput();
	}
	else
	{
		takeCoefficientInput();
	}

    solve();
}
