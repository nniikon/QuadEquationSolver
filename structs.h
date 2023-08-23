#pragma once
typedef struct {
    double a;
    double b;
    double c;
} Coefficients;

typedef struct {
    double x1;
    double x2;
    int answerType; // Number of answers.
} Answers;


enum ANSWERS_TYPES 
{
    NO_ROOTS,
    ONE_ROOT,
    ONE_DOUBLE_ROOT,
    TWO_ROOTS,
    INF_ROOTS,
};

void resetStructs(Coefficients* coefficients, Answers* answers);