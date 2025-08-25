#include "printer.h"

#include "../utils/double_comparator.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

char GetCoefficientName(const size_t index) {
    assert('a' + (char)index <= 'z');
    return 'a' + (char)index;
}

void PrintLetterPolynom(const size_t polynomPower) {
    for (size_t i = polynomPower; i > 1; i--)
        printf("%cx^%zu + ", GetCoefficientName(polynomPower-i), i);
    printf("%cx + ", GetCoefficientName(polynomPower-1));
    printf("%c = 0\n", GetCoefficientName(polynomPower));
}

void PrintPolynom(double *const coefficients, const size_t nCoefficients) {
    bool isFirst = true;
    for (size_t i = 0; i < nCoefficients; i++) {
        if (IsZero(coefficients[i]))
            continue;

        const double absValue = fabs(coefficients[i]);
        const bool isPositive = coefficients[i] > 0;

        if (!isPositive)   printf("-");
        else if (!isFirst) printf("+");
        
        if (!isFirst) printf(" ");

        if (i == nCoefficients-1 || !IsEqual(absValue, 1)) printf("%lg", absValue);

        if (i < nCoefficients-1) printf("x");
        if (i < nCoefficients-2) printf("^%zu", nCoefficients-1-i);
        printf(" ");
        isFirst = false;
    }
    if (isFirst) printf("0 ");
    printf("= 0\n");
}
