#include "commands.h"

#include "argument_parser.h"
#include "tester.h"
#include "square_solver.h"
#include "polynom/reader.h"
#include "utils/double_comparator.h"

#include <assert.h>
#include <stdio.h>
#include <math.h>

static void PrintRoots(RootCount nRoots, double x1, double x2);

const size_t N_COEFFICIENT = 3;
const size_t READ_ATTEMPT_LIMIT = 5;

extern bool shouldRunDefault;
extern Flag FLAGS[];
extern int FLAGS_LENGTH;


bool DefaultCommand(char *args[], int nArgs) {
    assert(nArgs == 0);
    TestCommand(NULL, 0);
    NoTestCommand(NULL, 0);
    return false;
}

bool PrintHelpCommand(char *args[], int nArgs) {
    assert(nArgs == 0);

    printf("help\n");
    PrintArgumentInfo(FLAGS, FLAGS_LENGTH);
    return false;
}

bool TestCommand(char *args[], int nArgs) {
    assert(nArgs == 0);

    RunTest();
    return false;
}

bool NoTestCommand(char *args[], int nArgs) {
    assert(nArgs == 0);

    double coefficients[N_COEFFICIENT] = {};
    for (size_t i = 0; i < N_COEFFICIENT; i++) coefficients[i] = NAN;
    
    if (ReadNCoefficientsWithAttempts(coefficients, N_COEFFICIENT, READ_ATTEMPT_LIMIT) != 0)
        return false;

    double x1 = NAN, x2 = NAN;
    const RootCount nRoots = SolveSquareEquation(
        coefficients[0],
        coefficients[1], 
        coefficients[2], 
        &x1, &x2
    );
    printf("Solving...\n\n");
    PrintRoots(nRoots, x1, x2);
    return false;
}


static void PrintRoots(RootCount nRoots, double x1, double x2) {
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
