#pragma once
typedef struct {
    double a;
    double b;
    double c;
} Coefficients;

typedef struct {
    double x1;
    double x2;
    int nAnswers; // Number of answers.
} Answers;

void resetStructs(Coefficients* coefficients, Answers* answers);
