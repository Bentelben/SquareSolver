#include "tester.h"
#include "square_solver.h"
#include "polynom_reader.h"
#include "double_comparator.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

void WriteOut(RootCount nRoots, double x1, double x2);

const size_t N_COEFFICIENT = 3;
const size_t READ_ATTEMPT_LIMIT = 5;

int main() {
    if (TestSquareSolver() == -1)
        return -1;

    double coefficients[N_COEFFICIENT] = {};
    for (size_t i = 0; i < N_COEFFICIENT; i++) coefficients[i] = NAN;
    
    if (ReadNCoefficientsWithAttempts(coefficients, N_COEFFICIENT, READ_ATTEMPT_LIMIT) != 0)
        return -1;

    double x1 = NAN, x2 = NAN;
    const RootCount nRoots = SolveSquareEquation(
        coefficients[0],
        coefficients[1], 
        coefficients[2], 
        &x1, &x2
    );
    WriteOut(nRoots, x1, x2);
}

void WriteOut(RootCount nRoots, double x1, double x2) {
    if (IsZero(x1)) x1 = 0;
    if (IsZero(x2)) x2 = 0;

    if (nRoots == TWO && IsEqual(x1, x2))
        nRoots = ONE;

    switch (nRoots) {
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
