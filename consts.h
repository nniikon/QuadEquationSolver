#pragma once

// Some values to play with
const int MAX_INPUT_LENGTH = 256;
const int MAX_CHUNK_LENGTH = 32;
const double EPSILON = 1e-10;
#define ALLOWED_EQUATION_INPUT_CHARACTERS "1234567890-+=xX*^., "
#define ALLOWED_COEFFICIENT_INPUT_CHARACTERS "1234567890.-"
#define ALLOWED_CONTINUE_INPUT_CHARACTERS "yYnN"
#define ALLOWED_AROUND_SPACE_CHARACTERS "+-=*"
#define RESTRICTED_AROUND_X_CHARACTERS "xX"

// Input types
enum INPUT_TYPE{COEFFICIENT_INPUT, EQUATION_INPUT};
#define INF 100

//#define DEBUG
//#define TEST
