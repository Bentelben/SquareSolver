#include <stdio.h>
#include <assert.h>
#include "input_reader.h"

const size_t ATTEMPT_COUNT = 5;

static int ReadOneDouble(const char name, double *const ptr) {
    assert(ptr != NULL);
    
    printf("Enter %c: ", name);
    char next_char = 0;
    const int read_result = scanf("%lf%c", ptr, &next_char); 
    if (read_result == 1 || (read_result == 2 && next_char == '\n'))
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
            if (ReadOneDouble('a' + (char)j, coefficients + j) != 0) {
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


