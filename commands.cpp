#include "commands.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "tester.h"
#include "square_solver.h"
#include "io/error.h"
#include "io/argument_parser.h"
#include "io/display_controller.h"
#include "utils/myassert.h"
#include "utils/ccomplex.h"
#include "utils/double_comparator.h"
#include "polynom/reader.h"

static void PrintRoots(RootCount nRoots, ccomplex x1, ccomplex x2);

const size_t N_COEFFICIENT = 3;
const size_t READ_ATTEMPT_LIMIT = 5;

extern const Flag FLAGS[];
extern const size_t FLAGS_LENGTH;

bool DefaultCommand(char *args[], int nArgs, void *context) {
    (void)args;
    myassert(nArgs == 0, "Wrong command argument count");
    myassert(context, "Context is NULL");

    FlagContext *flagContext = (FlagContext*)context;

    int testsFailed = RunTest(
        flagContext->test.filename,
        flagContext->test.shouldCompareNRoots,
        flagContext->test.verbose,
        flagContext->isComplex
    );
    if (!flagContext->test.ignore && testsFailed) {
        return false;
    }
    printf("Done testing\n\n");
    return NoTestCommand(NULL, 0, context);
}

bool PrintHelpCommand(char *args[], int nArgs, void *context) {
    (void)args;
    myassert(nArgs == 0, "Wrong command argument count");
    (void)context;

    ResetTextAttributes();
    printf("Here is help:\n");
    PrintArgumentInfo(FLAGS, FLAGS_LENGTH);
    return true;
}

bool TestCommand(char *args[], int nArgs, void *context) {
    (void)args;
    myassert(nArgs == 0, "Wrong command argument count");
    myassert(context, "Context is NULL");

    FlagContext *flagContext = (FlagContext*)context;

    RunTest(
        flagContext->test.filename,
        flagContext->test.shouldCompareNRoots,
        flagContext->test.verbose,
        flagContext->isComplex
    );
    return true;
}

bool SetTestFilenameCommand(char *args[], int nArgs, void *context) {
    myassert(args, "");
    myassert(nArgs == 1, "Wrong command argument count");
    myassert(context, "Context is NULL");

    ((FlagContext*)context)->test.filename = args[0];
    return true;
}

bool SetTestShouldCompareNRootsCommand(char *args[], int nArgs, void *context) {
    myassert(args != NULL, "");
    myassert(nArgs == 0, "Wrong command argument count");
    myassert(context, "Context is NULL");

    ((FlagContext*)context)->test.shouldCompareNRoots = false;
    return true;
}

bool SetTestVerboseCommand(char *args[], int nArgs, void *context) {
    myassert(args != NULL, "");
    myassert(nArgs == 0, "Wrong command argument count");
    myassert(context, "Context is NULL");

    ((FlagContext*)context)->test.verbose = true;
    return true;
}

bool SetTestIgnoreCommand(char *args[], int nArgs, void *context) {
    (void)args;
    myassert(nArgs == 0, "Wrong command argument count");
    myassert(context, "Context is NULL");

    ((FlagContext*)context)->test.ignore = true;
    return true;
}

bool NoTestCommand(char *args[], int nArgs, void *context) {
    (void)args;
    myassert(nArgs == 0, "Wrong command argument count");
    myassert(context, "Context is NULL");

    const bool isComplex = ((FlagContext*)context)->isComplex;

    ccomplex coefficients[N_COEFFICIENT] = {};

    if (ReadNCoefficientsWithAttempts(coefficients, N_COEFFICIENT, READ_ATTEMPT_LIMIT, isComplex) != 0) {
        PrintError("Attempt limit reached");
        return false;
    }

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
    return true;
}

bool SetIsComplexCommand(char *args[], int nArgs, void *context) {
    (void)args;
    myassert(nArgs == 0, "Wrong command argument count");
    myassert(context, "Context is NULL");

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
            myassert(!IsComplexNan(x1), "");
            printf("x = ");
            PrintComplex(x1);
            printf("\n");
            break;
        case RC_TWO:
            myassert(!IsComplexNan(x1) && !IsComplexNan(x2), "");
            printf("x1 = ");
            PrintComplex(x1);
            printf("\n");

            printf("x2 = ");
            PrintComplex(x2);
            printf("\n");
            break;
        default:
            myassert(0, "");
            break;
    }
}
