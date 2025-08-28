#include "tester.h"

#include <stdio.h>
#include <math.h>
#include "myassert.h"

#include "square_solver.h"
#include "utils/display_controller.h"
#include "utils/double_comparator.h"
#include "utils/ccomplex.h"
#include "utils/buffer_cleaner.h"

static bool IsEqualRoots(const RootCount nRoots, const ccomplex answer_x1, const ccomplex answer_x2, const ccomplex x1, const ccomplex x2) {
    if (nRoots == RC_INF || nRoots == RC_ZERO)
        return true;

    if (nRoots == RC_ONE)
        return IsComplexEqual(answer_x1, x1);
    else
        return (IsComplexEqual(answer_x1, x1) && IsComplexEqual(answer_x2, x2)) ||
               (IsComplexEqual(answer_x1, x2) && IsComplexEqual(answer_x2, x1));
}

static bool TestSquareSolver(
    const double a, const double b, const double c,
    const RootCount answer_nRoots, const ccomplex answer_x1, const ccomplex answer_x2,
    const bool shouldCompareNRoots, const bool verbose, const bool isComplex
) {
    ccomplex x1 = {};
    ccomplex x2 = {};

    const RootCount nRoots = SolveSquareEquation(a, b, c, &x1, &x2, isComplex);

    bool isCorrect = (!shouldCompareNRoots || nRoots == answer_nRoots) && IsEqualRoots(nRoots, answer_x1, answer_x2, x1, x2);

    if (isCorrect) {
        if (!verbose) return true;

        SetColor(GREEN, NORMAL, FOREGROUND);
        printf("OK");
    } else {
        SetColor(RED, NORMAL, BACKGROUND);
        printf("Wrong answer!");
    }

    printf("\na = %g b = %g c = %g\n", a, b, c);
    printf("got answer nRoots = %d x1 = ", nRoots);

    PrintComplex(x1);
    printf(" x2 = ");
    PrintComplex(x2);

    printf("\nshould be  nRoots = %d x1 = ", answer_nRoots);

    PrintComplex(answer_x1);
    printf(" x2 = ");
    PrintComplex(answer_x2);

    ResetTextAttributes();
    printf("\n");
    return isCorrect;
}

int RunTest(const char *filename, const bool shouldCompareNRoots, const bool verbose, const bool isComplex) {
    myassert(filename, "");

    printf("Testing...\n");

    FILE *testFile = fopen(filename, "r");
    myassert(testFile, "");

    double a = 0, b = 0, c = 0;
    RootCount nRoots = RC_INF;
    ccomplex x1 = {};
    ccomplex x2 = {};

    int failedTests = 0;
    int scanfCode = 0;
    while (true) {
        if ((scanfCode = fscanf(testFile, "%lg %lg %lg", &a, &b, &c)) != 3)
            break;

        if (shouldCompareNRoots)
            if ((scanfCode = fscanf(testFile, "%d", (int*)&nRoots)) != 1)
                break;

        if ((scanfCode = fscanf(testFile, "%lg %lg", &x1.real, &x2.real)) != 2)
            break;

        failedTests += !TestSquareSolver(a, b, c, nRoots, x1, x2, shouldCompareNRoots, verbose, isComplex);
    }

    fclose(testFile);

    if (scanfCode != EOF) {
        printf("Error on reading test file\n");
        return -1;
    }

    return failedTests;
}

