#include "commands.h"

#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "argument_parser.h"
#include "tester.h"
#include "square_solver.h"
#include "polynom/reader.h"
#include "utils/ccomplex.h"
#include "utils/double_comparator.h"

static void PrintRoots(RootCount nRoots, ccomplex x1, ccomplex x2);

const size_t N_COEFFICIENT = 3;
const size_t READ_ATTEMPT_LIMIT = 5;

extern const Flag FLAGS[];
extern const size_t FLAGS_LENGTH;

bool DefaultCommand(char *args[], int nArgs, void *context) {
    (void)args;
    assert(nArgs == 0);

    FlagContext *flagContext = (FlagContext*)context;
    
    int testsFailed = RunTest(
        flagContext->test.filename,
        flagContext->test.shouldCompareNRoots,
        flagContext->test.verbose,
        flagContext->isComplex
    );
    if (!flagContext->test.ignore && testsFailed)
        return false;
    printf("Done testing\n\n");
    NoTestCommand(NULL, 0, context);
    return false;
}

bool PrintHelpCommand(char *args[], int nArgs, void *context) {
    (void)args;
    assert(nArgs == 0);
    (void)context;

    printf("Here is help:\n");
    PrintArgumentInfo(FLAGS, FLAGS_LENGTH);
    return false;
}

bool TestCommand(char *args[], int nArgs, void *context) {
    (void)args;
    assert(nArgs == 0);

    FlagContext *flagContext = (FlagContext*)context;
    
    RunTest(
        flagContext->test.filename,
        flagContext->test.shouldCompareNRoots,
        flagContext->test.verbose,
        flagContext->isComplex
    );
    return false;
}

bool Test_set_filenameCommand(char *args[], int nArgs, void *context) {
    assert(args);
    assert(nArgs == 1);

    ((FlagContext*)context)->test.filename = args[0];
    return true;
}

bool Test_set_shouldCompareNRootsCommand(char *args[], int nArgs, void *context) {
    assert(nArgs == 0);
    assert(args != NULL);

    ((FlagContext*)context)->test.shouldCompareNRoots = false;
    return true;
}

bool Test_set_verboseCommand(char *args[], int nArgs, void *context) {
    assert(nArgs == 0);
    assert(args != NULL);

    ((FlagContext*)context)->test.verbose = true;
    return true;
}

bool Test_set_ignoreCommand(char *args[], int nArgs, void *context) {
    (void)args;
    assert(nArgs == 0);

    ((FlagContext*)context)->test.ignore = true;
    return true;
}

bool NoTestCommand(char *args[], int nArgs, void *context) {
    (void)args;
    assert(nArgs == 0);

    const bool isComplex = ((FlagContext*)context)->isComplex;

    double coefficients[N_COEFFICIENT] = {};
    for (size_t i = 0; i < N_COEFFICIENT; i++) coefficients[i] = NAN;
    
    if (ReadNCoefficientsWithAttempts(coefficients, N_COEFFICIENT, READ_ATTEMPT_LIMIT) != 0)
        return false;

    ccomplex x1 = {NAN, NAN};
    ccomplex x2 = {NAN, NAN};
    const RootCount nRoots = SolveSquareEquation(
        coefficients[0],
        coefficients[1], 
        coefficients[2], 
        &x1, &x2,
        isComplex 
     );
    printf("Solving...\n\n");
    PrintRoots(nRoots, x1, x2);
    return false;
}

bool Set_isComplexCommand(char *args[], int nArgs, void *context) {
    (void)args;
    assert(nArgs == 0);
    
    ((FlagContext*)context)->isComplex = true;
    return true;
}

static void PrintRoots(RootCount nRoots, ccomplex x1, ccomplex x2) {
    ZeroizeComplex(&x1);
    ZeroizeComplex(&x2);

    if (nRoots == RC_TWO && IsComplexEqual(x1, x2))
        nRoots = RC_ONE;

    switch (nRoots) {
        case RC_INF:
            printf("x is any real number\n");
            break;
        case RC_ZERO:
            printf("x is not real number\n");
            break;
        case RC_ONE:
            assert(!IsComplexNan(x1));
            printf("x = ");
            PrintComplex(x1);
            printf("\n");
            break;
        case RC_TWO:
            assert(!IsComplexNan(x1) && !IsComplexNan(x2));
            printf("x1 = ");
            PrintComplex(x1);
            printf("\n");

            printf("x2 = ");
            PrintComplex(x2);
            printf("\n");
            break;
        default:
            assert(0);
            break;
    }
}
