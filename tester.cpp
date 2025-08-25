#include "tester.h"

#include <stdio.h>
#include <math.h>

#include "square_solver.h"
#include "utils/display_controller.h"
#include "utils/double_comparator.h"
#include "utils/buffer_cleaner.h"

static bool IsEqualRoots(const RootCount nRoots, const double answer_x1, const double answer_x2, const double x1, const double x2) {
    if (nRoots == RC_INF || nRoots == RC_ZERO)
        return true;
    
    if (nRoots == RC_ONE) 
        return IsEqual(answer_x1, x1);
    else 
        return (IsEqual(answer_x1, x1) && IsEqual(answer_x2, x2)) ||
               (IsEqual(answer_x1, x2) && IsEqual(answer_x2, x1));
}

static bool TestSquareSolver(
    const double a, const double b, const double c,
    const RootCount answer_nRoots, const double answer_x1, const double answer_x2,
    const bool shouldCompareNRoots, const bool verbose
) {
    double x1 = 0;
    double x2 = 0;

    const RootCount nRoots = SolveSquareEquation(a, b, c, &x1, &x2);

    if ((!shouldCompareNRoots || nRoots == answer_nRoots) && IsEqualRoots(nRoots, answer_x1, answer_x2, x1, x2)) {
        if (verbose) {
            SetColor(GREEN, NORMAL, FOREGROUND);
            printf("OK");
            ResetTextAttributes();
            printf("\n");
        }
        return true;
    }
    
    SetColor(RED, NORMAL, BACKGROUND);
    printf("Wrong answer!\n"
           "a = %g b = %g c = %g\n", a, b, c);
    printf("got answer nRoots = %d x1 = %g x2 = %g\n", nRoots, x1, x2);
    printf("should be  nRoots = %d x1 = %g x2 = %g", answer_nRoots, answer_x1, answer_x2);
    ResetTextAttributes();
    printf("\n");
    return false;
}

int RunTest(const char *filename, const bool shouldCompareNRoots, const bool verbose) {
    printf("Testing...\n");

    FILE *testFile = fopen(filename, "r");

    double a = 0, b = 0, c = 0;
    RootCount nRoots = RC_INF;
    double x1 = NAN, x2 = NAN;

    int failedTests = 0;
    int scanfCode = 0;
    while (true) {
        if (shouldCompareNRoots) {
            scanfCode = fscanf(testFile, "%lg %lg %lg %d %lg %lg", &a, &b, &c, (int*)&nRoots, &x1, &x2);
            if (scanfCode != 6) break;
        } else {
            scanfCode = fscanf(testFile, "%lg %lg %lg %lg %lg", &a, &b, &c, &x1, &x2);
            if (scanfCode != 5) break;
        }
        failedTests += !TestSquareSolver(a, b, c, nRoots, x1, x2, shouldCompareNRoots, verbose);
    }
    
    if (scanfCode != EOF) {
        printf("Error on reading test file\n");
        return -1;
    }
    
    return failedTests;
}

