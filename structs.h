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

// Infinite number of solutions.
// "K O C T bl Jl b" fix asap
const int INF = 100;

void resetStructs(Coefficients* coefficients, Answers* answers);
