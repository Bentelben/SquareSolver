#include <stdio.h>
#include <assert.h>
#include "input_reader.h"

const size_t ATTEMPT_COUNT = 5;

static int ReadCoefficient(const char coefficientName, double *const resultValue) {
    assert(resultValue != NULL);
    
    printf("Enter %c: ", coefficientName);
    if (scanf("%lf", resultValue) != 1)
        return -1;
    
    int nextChar = getchar();
    if (nextChar == EOF || nextChar == '\n')
        return 0;
    return -1;
}

static void ClearStdinBuffer() {
    int c = '\0';
    do {
        c = getchar();
    } while (c != EOF && c != '\n');
}

int ReadIn(double *const coefficients, const size_t nCoefficient) {
    assert(coefficients != NULL);

    for (size_t i = 0; i < ATTEMPT_COUNT; i++) {
        if (i > 0) printf("Attemt %lu/%lu\n", i+1, ATTEMPT_COUNT);
        
        bool isRead = true;
        for (size_t j = 0; j < nCoefficient; j++) {
            if (ReadCoefficient('a' + (char)j, coefficients + j) != 0) {
                printf("Wrong input\n\n");
                isRead = false;
                ClearStdinBuffer();
                break;
            }
        }
        if (isRead) return 0;
    }
    return -1;
}


