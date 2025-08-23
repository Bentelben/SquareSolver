#include <stdio.h>
#include <assert.h>
#include "input_reader.h"

const size_t ATTEMPT_COUNT = 5;

static int readOneDouble(const char name, double *const ptr) {
    assert(ptr != NULL);
    
    printf("Enter %c: ", name);
    char next_char = 0;
    const int read_result = scanf("%lf%c", ptr, &next_char); 
    if (read_result == 1 || (read_result == 2 && next_char == '\n'))
        return 0;
    return -1;
}

//! Reads coefficients for polynom  of power coefficient_count-1 from console
//!
//! @param[out] coefficients      Array of coefficients
//! @param[in]  coefficient_count Length of array
//!
//! @return Zero on success and negative value on error
int readIn(double *const coefficients, const size_t coefficient_count) {
    assert(coefficients != NULL);

    for (size_t i = 0; i < ATTEMPT_COUNT; i++) {
        if (i > 0) printf("Attemt %lu/%lu\n", i+1, ATTEMPT_COUNT);
        
        bool isRead = true;
        for (size_t j = 0; j < coefficient_count; j++) {
            if (readOneDouble('a' + (char)j, coefficients + j) != 0) {
                printf("Wrong input\n\n");
                while (getchar() != '\n');
                isRead = false;
                break;
            }
        }
        if (isRead) return 0;
    }
    return -1;
}


