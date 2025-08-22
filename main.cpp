#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "square_solver.h"
#include "double_comparator.h"

const size_t ATTEMPT_COUNT = 5;

int readOneDouble(const char name, double *ptr);
int readIn(double *const coefficients, const size_t COEFFICIENT_COUNT);
void writeOut(RootCount root_count, double x1, double x2);

int main() {
    const size_t COEFFICIENT_COUNT = 3;
    double coefficients[COEFFICIENT_COUNT];
    
    printf("ax^2 + bx + c = 0\n");

    if (readIn(coefficients, COEFFICIENT_COUNT) != 0)
        return -1;

    printf("Solving %gx^2 + %gx + %g = 0\n", coefficients[0], coefficients[1], coefficients[2]);

    double x1 = NAN, x2 = NAN;
    const RootCount root_count = solveSquareEquation(
        coefficients[0],
        coefficients[1], 
        coefficients[2], 
        &x1, &x2
    );
    writeOut(root_count, x1, x2);
}

int readOneDouble(const char name, double *const ptr) {
    assert(ptr != NULL);
    
    printf("Enter %c: ", name);
    char next_char = 0;
    const int read_result = scanf("%lf%c", ptr, &next_char); 
    if (read_result == 1 || (read_result == 2 && next_char == '\n'))
        return 0;
    return -1;
}

int readIn(double *const coefficients, const size_t COEFFICIENT_COUNT) {
    for (size_t i = 0; i < ATTEMPT_COUNT; i++) {
        if (i > 0) printf("Attemt %lu/%lu\n", i+1, ATTEMPT_COUNT);
        
        bool isRead = true;
        for (size_t j = 0; j < COEFFICIENT_COUNT; j++) {
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

void writeOut(RootCount root_count, double x1, double x2) {
    if (isZero(x1)) x1 = 0;
    if (isZero(x2)) x2 = 0;

    if (root_count == TWO && isEqual(x1, x2))
        root_count = ONE;

    switch (root_count) {
        case INF:
            printf("x is any real number\n");
            break;
        case ZERO:
            printf("x is not real number\n");
            break;
        case ONE:
            assert(!isnan(x1));
            printf("x = %g\n", x1);
            break;
        case TWO:
            assert(!isnan(x1) && !isnan(x2));
            printf("x1 = %g\n", x1);
            printf("x2 = %g\n", x2);
            break;
        default:
            assert(0);
            break;
    }
}
