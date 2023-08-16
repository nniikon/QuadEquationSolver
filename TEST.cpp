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
#define MAX_CHUNK_LENGTH 32
#define EPSILON 0.0000001
#define allowedCharacters "1234567890-+=xX*^., "

// Отвечает за выбор типа ввода
bool isEquationInput = true;

//#define DEBUG // режим отладки

double a, b, c; // a*x^2 + b*x + c

// Запрашивает ввод, задает a, b, c. Использует ввод коэффициентов по-отдельности
void takeCoefficientInput();
// Запрашивает ввод, задает a, b, c. Использует ввод строки целиком
void takeEquationInput();
// Запрашивает коэффициент
void askCoefficient(double* coef, const char name);
// Проверяет строку на корректность
bool isCorrect(const char* input);
// Стандартизирует строку, может поменять длину
void toDefault(char* input, unsigned int* inputLength);
// Убирает символы из строки
void deleteCharacter(char* input, unsigned int* inputLength, const char character);
// Задаёт a, b, c. Работает со стандартизированной строкой
void setCoefficients(char* input);
// Задает коэффициенты из кусочков строки ввода. Работет с setCoefficients
void setChunk(char* chunk, bool passedEqualSign);
// Красиво выводит уравнение
void formattedCout();
// Решает уравнение
void solve();
// Сравниваем double
bool areSameDouble(double f, double s);


int main()
{
	// Спрашиваем у пользователя желаемый вид ввода
	printf("%s%s%s", "What type of input would you prefer?\n",
			"(1) Coefficient input\n",
			"(2) Equation input\n");
	char choice = getchar();
	if(choice == '1')
		isEquationInput = false;
	else if(choice == '2')
		isEquationInput = true;
	else
	{
		printf("Invalid input. But I really like the second option, so I chose it for you =\)\n");
	}
	// Чистим буфер
	while(getchar() != '\n');

	// Запрашиваем ввод пользователя
	if(isEquationInput)
	{
		takeEquationInput();
	}
	else
	{
		takeCoefficientInput();
	}

	// Красиво выводим
	formattedCout();

	// Решаем
    solve();
}

void takeEquationInput()
{
	// Создадим строку, в которой будет храниться ввод пользователя
	char input[MAX_INPUT_LENGTH];
	do
	{
		// Запрашивает ввод
		printf("Enter your equation: ");
		scanf("%[^\n]", input);
		// Проверяем корректность ввода
		if (!isCorrect(input))
		{
			printf("Invalid input.\n"); // Ругаем пользователя
			input[0] = '\n'; // "очищаем" строку
			while (getchar() != '\n'); // очищаем буфер
		}
	} while (!isCorrect(input));

    unsigned int inputLength = strlen(input); // длина строки

	// Приведем к стандартному виду
	toDefault(input, &inputLength);

	// Зададим коэффициенты
	setCoefficients(input);

	#ifdef DEBUG
		printf("\nDEBUG: standartised equation: %s\n", input);
        printf("DEBUG: a = %f \nDEBUG: b = %f \nDEBUG: c = %f\n\n", a, b, c);
    #endif

}

bool isCorrect(const char* input)
{
    bool isListed;

    // Проходим по каждому символу во входной строке.
    for(unsigned int i = 0; i < strlen(input); i++)
    {
        isListed = false;

        // Проверяем, присутствует ли текущий символ среди разрешенных символов.
        for(unsigned int j = 0; j < strlen(allowedCharacters); j++)
        {
            if(input[i] == allowedCharacters[j])
            {
                isListed = true;
                break;
            }
        }

        // Если текущий символ не найден среди разрешенных, возвращаем false.
        if(!isListed)
            return false;
    }

    // Если все символы прошли проверку, возвращаем true.
    return true;
}

void deleteCharacter(char* input, unsigned int* inputLength, const char character)
{
	// Переменная для отслеживания текущей позиции, на которую будет перенесен следующий символ.
	int currentEmptySpace = 0;

	// Проходимся по всей исходной строке.
	for(unsigned int i = 0; i < *inputLength; i++)
	{
		// Если текущий символ не совпадает с символом, который нужно удалить...
		if(input[i] != character)
		{
			// Переносим текущий символ на позицию текущего "пустого" места и увеличиваем его.
			input[currentEmptySpace] = input[i];
			currentEmptySpace++;
		}
	}

	// Обновляем длину строки после удаления символов.
	*inputLength = currentEmptySpace;

	// Добавляем завершающий нулевой символ, чтобы строка оставалась корректной.
	input[currentEmptySpace] = '\0';
}

void toDefault(char* input, unsigned int* inputLength)
{
	/*
	Стандартная строка должна выглядить примерно так:

	5x^2-6x+12=5x-12x^2

	*/
	// Удаляем необязательные символы
	deleteCharacter(input, inputLength, ' ');
	deleteCharacter(input, inputLength, '*');

	// Стандартизируем похожие знаки
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

void setChunk(char* chunk, bool passedEqualSign)
{
	/*
	Эта функция принимает кусок строки ввода и задает с его помощью коэффициенты
	Примеры ввода:
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

	// Определим, к какому коэффициенту мы будем прибавлять value

	// Если строка заканчивается на x^2, то прибавляем к а
	if (len >= 3 && chunk[len - 3] == 'x' && chunk[len - 2] == '^' && chunk[len - 1] == '2')
	{
		isA = true;

		// Рассмотрим случаи x^2, +x^2, -x^2
		if( (len == 3) || (len == 4 && (chunk[0] == '-' || chunk[0] == '+')) )
		{
			// Тогда вместо x удобно поставить единичку, которую люди не любят писать
			chunk[len - 3] = '1';
		}
	}
	// Если строка заканчивается на x, то прибавляем к b
	else if (len >= 1 && chunk[len - 1] == 'x')
	{
		isB = true;

		// Рассмотрим случаи x, +х, -х
		if( (len == 1) || (len == 2 && (chunk[0] == '-' || chunk[0] == '+')) )
		{
			// Тогда вместо x удобно поставить единичку, которую люди не любят писать
			chunk[len - 1] = '1';
		}
	}
	// В любом другом случае, это просто число, прибавляем к c
	else
	{
		isC = true;
	}

	// Зададим value
	value = atof(chunk);

	// Если мы по правую сторону уравнения, то переносим влево (с минусом)
	if (passedEqualSign)
	{
		value = -value;
	}

	// Ну и прибавляем value к коэффициентам
	if(isA)
	{
		a += value;
		return;
	}
	if(isB)
	{
		b += value;
		return;
	}
	if(isC)
	{
		c += value;
		return;
	}
}

void setCoefficients(char* input)
{
    bool passedEqualSign = false;  // Флаг для отслеживания, прошли ли знак равенства
    int len = strlen(input);        // Длина входной строки
    char strChunk[MAX_CHUNK_LENGTH]{};  // Временный буфер для хранения кусков строки
    int chunkCounter = 0;           // Счетчик для индекса буфера

    // Пройдемся по исходной строке
    for (int i = 0; i <= len; i++)
    {
        // Если дошли до разделяющего знака (+, -, =, \0)
        if (input[i] == '+' || input[i] == '-' || input[i] == '=' || input[i] == '\0')
        {
            strChunk[chunkCounter] = '\0';  // Завершаем строку в буфере
            chunkCounter = 0;  // Сбрасываем счетчик для следующего куска
            setChunk(strChunk, passedEqualSign);  // Обрабатываем кусок

            // Если текущий знак - равенство, устанавливаем флаг
            if (input[i] == '=')
            {
                passedEqualSign = true;
                continue; // Пропустим итерацию, чтобы равно не помешало обработке
            }
        }

        strChunk[chunkCounter] = input[i];  // Добавляем символ в буфер
        chunkCounter++;  // Увеличиваем счетчик буфера
    }
}


void formattedCout()
{
	// Просто красиво выводим уравнение, ничего интересного
	if (a == 0 && b == 0)
	{
		if (c == 0)
			printf("0 == 0\n");
		else
			printf("%g != 0\n", c);
		return;
	}

    if (a != 0)
	{
        if (a == -1)
            printf("-x^2 ");
        else if (a == 1)
            printf("x^2 ");
        else
            printf("%gx^2 ", a);
    }

    if (b != 0)
	{
        if (b < 0)
            printf("- ");
        else if (a != 0)
            printf("+ ");

        if (b == -1)
            printf("x ");
        else if (b == 1)
            printf("x ");
        else
            printf("%gx ", fabs(b));
    }

    if (c != 0)
    {
        if (c < 0)
            printf("- %g ", -c);
        else if (b != 0)
            printf("+ %g ", c);
        else
            printf("%g ", c);
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
		printf("Please enter coefficient %c: ", name);
		validInput = scanf("%lf", coef);
		#ifdef DEBUG
			printf("validInput: %d\nNumber %c = %f\n", validInput, name ,*coef);
		#endif
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
}
