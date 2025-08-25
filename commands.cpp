#include "commands.h"

#include "argument_parser.h"
#include "tester.h"
#include "square_solver.h"
#include "polynom/reader.h"
#include "utils/double_comparator.h"

#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

static bool ParseBoolean(char *arg);
static void PrintRoots(RootCount nRoots, double x1, double x2);

const size_t N_COEFFICIENT = 3;
const size_t READ_ATTEMPT_LIMIT = 5;

extern Flag FLAGS[];
extern int FLAGS_LENGTH;

extern char* test_filename;
extern bool test_shouldCompareNRoots;
extern bool test_verbose;
extern bool test_ignore;

bool DefaultCommand(char *args[], int nArgs) {
    assert(nArgs == 0);

    int testsFailed = RunTest(test_filename, test_shouldCompareNRoots, test_verbose);
    if (!test_ignore && testsFailed)
        return false;
    printf("Done testing\n\n");
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

    RunTest(test_filename, test_shouldCompareNRoots, test_verbose);
    return false;
}
bool Test_set_filenameCommand(char *args[], int nArgs) {
    assert(nArgs == 1);

    test_filename = args[0];
    return true;
}bool Test_set_shouldCompareNRootsCommand(char *args[], int nArgs) {
    assert(nArgs == 1);

    test_shouldCompareNRoots = ParseBoolean(args[0]);
    return true;
}
bool Test_set_verboseCommand(char *args[], int nArgs) {
    assert(nArgs == 1);

    test_verbose = ParseBoolean(args[0]);
    return true;
}
bool Test_set_ignoreCommand(char *args[], int nArgs) {
    assert(nArgs == 0);

    test_ignore = true;
    return true;
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

static bool ParseBoolean(char *arg) {
    if (strcmp(arg, "true")==0 || strcmp(arg, "1")==0) return true;
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
