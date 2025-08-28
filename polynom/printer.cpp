#include "printer.h"

#include "../utils/double_comparator.h"
#include "../utils/ccomplex.h"

#include <stdio.h>
#include <math.h>
#include "../myassert.h"

char GetCoefficientName(const size_t index) {
    myassert('a' + (char)index <= 'z', "Coefficient name is not in [a-z]");
    return 'a' + (char)index;
}

void PrintLetterPolynom(const size_t polynomPower) {
    for (size_t i = polynomPower; i > 1; i--)
        printf("%cx^%zu + ", GetCoefficientName(polynomPower-i), i);
    printf("%cx + ", GetCoefficientName(polynomPower-1));
    printf("%c = 0\n", GetCoefficientName(polynomPower));
}

void PrintPolynom(ccomplex *const coefficients, const size_t nCoefficients) {
    myassert(coefficients, "Ptr to array of coefficients is zero");

    bool isFirst = true;
    for (size_t i = 0; i < nCoefficients; i++) {
        if (IsComplexZero(coefficients[i]))
            continue;

        if (!IsZero(coefficients[i].real) && !IsZero(coefficients[i].imag)) {
            printf("+ ");
            PrintComplex(coefficients[i]);
        } else {
            const bool isImag = IsZero(coefficients[i].real);
            const double value = (isImag) ? coefficients[i].imag : coefficients[i].real;
            const double absValue = fabs(value);
            const bool isPositive = value > 0;

            if (!isPositive)   printf("-");
            else if (!isFirst) printf("+");

            if (!isFirst) printf(" ");

            if ((i == nCoefficients-1 && !isImag) || !IsEqual(absValue, 1)) printf("%lg", absValue);
            if (isImag) printf("i");
        }

        if (i < nCoefficients-1) printf("x");
        if (i < nCoefficients-2) printf("^%zu", nCoefficients-1-i);
        printf(" ");
        isFirst = false;
    }
    if (isFirst) printf("0 ");
    printf("= 0\n");
}
