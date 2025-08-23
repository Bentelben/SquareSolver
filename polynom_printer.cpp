#include "polynom_printer.h"

#include "double_comparator.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

static void PrintSpacedSignedValue(const double value) {
    printf("%c %lg", (value < 0) ? '-' : '+', value);
}

char GetCoefficientName(const size_t index) {
    assert('a' + (char)index <= 'z');
    return 'a' + (char)index;
}

void PrintLetterPolynom(const size_t polynomPower) {
    for (size_t i = polynomPower; i > 1; i--)
        printf("%cx^%lu + ", GetCoefficientName(polynomPower-i), i);
    printf("%cx + ", GetCoefficientName(polynomPower-1));
    printf("%c = 0\n", GetCoefficientName(polynomPower));
}

void PrintPolynom(const double *const coefficients, const size_t nCoefficients) {
    bool isNotZero = false;
    for (size_t i = 0; i < nCoefficients; i++) {
        if (IsZero(coefficients[i])) continue;
        isNotZero = true;
        if (!IsEqual(coefficients[i], 1)) {
            if (i == 0) printf("%lg", coefficients[i]);
            else PrintSpacedSignedValue(coefficients[i]);
        }
        if (i < nCoefficients-1) printf("x");
        if (i < nCoefficients-2) printf("^%lu", nCoefficients-1-i);
        printf(" ");
    }
    if (!isNotZero) printf("0 ");
    printf("= 0\n");
}
