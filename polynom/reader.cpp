#include "reader.h"

#include "printer.h"
#include "../utils/buffer_cleaner.h"

#include <stdio.h>
#include <assert.h>

int ReadCoefficient(const char coefficientName, double *const resultValue) {
    assert(resultValue != NULL);
    
    printf("Enter %c: ", coefficientName);
    if (scanf("%lg", resultValue) != 1)
        return -1;
    
    const int nextChar = getchar();
    if (nextChar == EOF || nextChar == '\n')
        return 0;
    return -1;
}

int ReadNCoefficients(double *const resultCoefficients, const size_t nCoefficient) {
    assert(resultCoefficients != NULL);

    PrintLetterPolynom(nCoefficient-1);

    for (size_t i = 0; i < nCoefficient; i++)
        if (ReadCoefficient(GetCoefficientName(i), resultCoefficients + i) != 0)
            return -1;
    PrintPolynom(resultCoefficients, nCoefficient);
    return 0;
}

int ReadNCoefficientsWithAttempts(double *const resultCoefficients, const size_t nCoefficient, const size_t attemptLimit) {
    assert(resultCoefficients != NULL);

    for (size_t i = 0; i < attemptLimit; i++) {
        if (i > 0)
            printf("Attemt %lu/%lu\n", i+1, attemptLimit);
        if (ReadNCoefficients(resultCoefficients, nCoefficient) != -1)
            return 0;
        printf("Wrong input\n\n");
        CleanBufferLine(stdin);
    }
    return -1;
}
