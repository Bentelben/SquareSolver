#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "input_reader.h"
#include "square_solver.h"
#include "double_comparator.h"

void writeOut(RootCount root_count, double x1, double x2);

int main() {
    const size_t COEFFICIENT_COUNT = 3;
    double coefficients[COEFFICIENT_COUNT] = {};
    for (size_t i = 0; i < COEFFICIENT_COUNT; i++) coefficients[i] = NAN;
    
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
