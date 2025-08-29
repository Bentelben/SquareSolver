#include "reader.h"

#include <stdio.h>

#include "printer.h"
#include "../io/buffer_cleaner.h"
#include "../utils/myassert.h"
#include "../utils/ccomplex.h"
#include "../utils/double_comparator.h"

int ReadCoefficient(const char coefficientName, ccomplex *const resultValue, const bool isComplex) {
    myassert(resultValue, "Ptr for out value is NULL");

    printf("Enter %c: ", coefficientName);
    if (ScanComplex(resultValue) != 1)
        return -1;

    if (!isComplex && !IsZero(resultValue->imag)) return -1;

    const int nextChar = getchar();
    if (nextChar == EOF || nextChar == '\n')
        return 0;
    return -1;
}

int ReadNCoefficients(ccomplex *const resultCoefficients, const size_t nCoefficient, const bool isComplex) {
    myassert(resultCoefficients, "Ptr for out array of coefficients is NULL");

    PrintLetterPolynom(nCoefficient-1);

    for (size_t i = 0; i < nCoefficient; i++)
        if (ReadCoefficient(GetCoefficientName(i), resultCoefficients + i, isComplex) != 0)
            return -1;
    PrintPolynom(resultCoefficients, nCoefficient);
    return 0;
}

int ReadNCoefficientsWithAttempts(ccomplex *const resultCoefficients, const size_t nCoefficient, const size_t attemptLimit, const bool isComplex) {
    myassert(resultCoefficients, "Ptr for out array of coefficients is NULL");

    for (size_t i = 0; i < attemptLimit; i++) {
        if (i > 0)
            printf("Attempt %lu/%lu\n", i+1, attemptLimit);
        if (ReadNCoefficients(resultCoefficients, nCoefficient, isComplex) != -1)
            return 0;
        printf("Wrong input\n\n");
        CleanBufferLine(stdin);
    }
    return -1;
}
