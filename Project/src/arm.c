#include "arm.h"

unsigned int __uidiv(unsigned int numerator, unsigned int denominator)
{
    unsigned int division = 0;
    int temp = numerator;
    if (numerator == 0 || denominator == 0)
    {
        return 0;
    }

    if (denominator > 0)
    {
        while (temp > 0)
        {
            division++;
            temp -= denominator;
        }
    }

    return division - 1;
}


unsigned __aeabi_uidiv(unsigned numerator, unsigned denominator)
{
    return __uidiv(numerator, denominator);
}


unsigned __aeabi_uldivmod(unsigned a, unsigned b)
{
    if (b == 0) {
        return 0;
    }

    while (a > b) {
        a -= b;
    }

    return a;
}
