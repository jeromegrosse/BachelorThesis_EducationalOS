#include "math.h"

int abs(int number)
{
    return number < 0 ? -number : number;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}
