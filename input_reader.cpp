#include "input_reader.h"
#include <stdio.h>

#include <assert.h>

static void ClearStdinBuffer();

int ReadCoefficient(const char coefficientName, double *const resultValue) {
    assert(resultValue != NULL);
    
    printf("Enter %c: ", coefficientName);
    if (scanf("%lf", resultValue) != 1)
        return -1;
    
    int nextChar = getchar();
    if (nextChar == EOF || nextChar == '\n')
        return 0;
    return -1;
}

int ReadNCoefficients(double *const resultCoefficients, const size_t nCoefficient) {
    assert(resultCoefficients != NULL);
    assert(nCoefficient > 0);

    for (size_t i = 0; i < nCoefficient; i++)
        if (ReadCoefficient('a' + (char)i, resultCoefficients + i) != 0)
            return -1;
    return 0;
}

int ReadNCoefficientsWithAttempts(double *const resultCoefficients, const size_t nCoefficient, const size_t attemptLimit) {
    assert(resultCoefficients != NULL);
    assert(nCoefficient > 0);

    for (size_t i = 0; i < attemptLimit; i++) {
        if (i > 0)
            printf("Attemt %lu/%lu\n", i+1, attemptLimit);
        if (ReadNCoefficients(resultCoefficients, nCoefficient) != -1)
            return 0;
        printf("Wrong input\n\n");
        ClearStdinBuffer();
    }
    return -1;
}

static void ClearStdinBuffer() {
    int c = '\0';
    do {
        c = getchar();
    } while (c != EOF && c != '\n');
}
