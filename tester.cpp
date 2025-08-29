#include "tester.h"

#include <math.h>
#include <stdio.h>

#include "square_solver.h"
#include "io/error.h"
#include "io/buffer_cleaner.h"
#include "io/display_controller.h"
#include "utils/ccomplex.h"
#include "utils/myassert.h"
#include "utils/double_comparator.h"

static bool IsEqualRoots(const RootCount nRoots, const ccomplex answer_x1, const ccomplex answer_x2, const ccomplex x1, const ccomplex x2) {
    if (nRoots == RC_INF || nRoots == RC_ZERO)
        return true;

    if (nRoots == RC_ONE)
        return IsComplexEqual(answer_x1, x1);
    else
        return (IsComplexEqual(answer_x1, x1) && IsComplexEqual(answer_x2, x2)) ||
               (IsComplexEqual(answer_x1, x2) && IsComplexEqual(answer_x2, x1));
}

static void PrintTestResult(const char *text, const RootCount nRoots, const ccomplex x1, const ccomplex x2) {
    printf("\n%s nRoots = %d x1 = ", text, nRoots);
    PrintComplex(x1);
    printf(" x2 = ");
    PrintComplex(x2);
}

static bool TestSquareSolver(
    const ccomplex a, const ccomplex b, const ccomplex c,
    const RootCount answer_nRoots, const ccomplex answer_x1, const ccomplex answer_x2,
    const bool shouldCompareNRoots, const bool verbose, const bool isComplex
) {
    ccomplex x1 = {NAN, NAN};
    ccomplex x2 = {NAN, NAN};

    const RootCount nRoots = SolveSquareEquation(a, b, c, &x1, &x2, isComplex);

    const bool isCorrect = (!shouldCompareNRoots || nRoots == answer_nRoots) && IsEqualRoots(nRoots, answer_x1, answer_x2, x1, x2);

    if (isCorrect) {
        if (!verbose) return true;

        SetColor(GREEN, NORMAL, FOREGROUND);
        printf("OK");
    } else {
        SetColor(RED, NORMAL, BACKGROUND);
        printf("Wrong answer!");
    }

    printf("\na = ");
    PrintComplex(a);
    printf(" b = ");
    PrintComplex(b);
    printf(" c = ");
    PrintComplex(c);

    PrintTestResult("got result", nRoots, x1, x2);
    PrintTestResult("should be ", answer_nRoots, answer_x1, answer_x2);

    ResetTextAttributes();
    printf("\n");
    return isCorrect;
}

static int ScanTest(FILE *const testFile, ccomplex *const a, ccomplex *const b, ccomplex *const c, RootCount *const nRoots, ccomplex *const x1, ccomplex *const x2, const bool shouldCompareNRoots) {
    myassert(testFile, "Ptr to file is NULL");
    myassert(a, "Ptr to a is NULL");
    myassert(b, "Ptr to b is NULL");
    myassert(c, "Ptr to c is NULL");
    myassert(nRoots, "Ptr to nRoots is NULL");
    myassert(x1, "Ptr to x1 is NULL");
    myassert(x2, "Ptr to x2 is NULL");

    if (FScanComplex(testFile, a) != 1)
        return 0;

    if (FScanComplex(testFile, b) != 1)
        return -1;
    if (FScanComplex(testFile, c) != 1)
        return -1;

    if (shouldCompareNRoots)
        if (fscanf(testFile, "%d", (int*)nRoots) != 1)
            return -1;

    if (FScanComplex(testFile, x1) != 1)
        return -1;
    if (FScanComplex(testFile, x2) != 1)
        return -1;
    return 1;
}

int RunTest(const char *const filename, const bool shouldCompareNRoots, const bool verbose, const bool isComplex) {
    myassert(filename, "Filename is NULL");

    printf("Testing...\n");

    FILE *const testFile = fopen(filename, "r");
    if (testFile == NULL) {
        PrintError("Unable to open file `%s`", filename);
        return -1;
    }

    RootCount nRoots = RC_INF;
    ccomplex x1 = {};
    ccomplex x2 = {};
    ccomplex a  = {};
    ccomplex b  = {};
    ccomplex c  = {};

    int failedTests = 0;
    int scanCode = 1;
    while (true) {
        scanCode = ScanTest(testFile, &a, &b, &c, &nRoots, &x1, &x2, shouldCompareNRoots);
        if (scanCode != 1)
            break;
        failedTests += !TestSquareSolver(a, b, c, nRoots, x1, x2, shouldCompareNRoots, verbose, isComplex);
    }

    fclose(testFile);

    if (scanCode == -1) {
        PrintError("Reading test file failed");
        return -1;
    }

    printf("Done testing\n");
    return failedTests;
}
