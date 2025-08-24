#include "tester.h"

#include "square_solver.h"
#include "utils/display_controller.h"
#include "utils/double_comparator.h"
#include "utils/buffer_cleaner.h"

#include <stdio.h>
#include <math.h>

const char *TEST_FILENAME = "test.txt";

static void TestSquareSolver(
    const double a, const double b, const double c,
    const RootCount answer_nRoots, const double answer_x1, const double answer_x2
) {
    double x1 = 0, x2 = 0;
    const RootCount nRoots = SolveSquareEquation(a, b, c, &x1, &x2);
    if (nRoots == answer_nRoots && IsEqual(x1, answer_x1) && IsEqual(x2, answer_x2)) {
        SetColor(GREEN, NORMAL, FOREGROUND);
        printf("OK");
    }
    else {
        SetColor(RED, NORMAL, BACKGROUND);
        printf("Wrong answer!\n");
        printf("a = %g b = %g c = %g\n", a, b, c);
        printf("got answer nRoots = %d x1 = %g x2 = %g\n", nRoots, x1, x2);
        printf("should be  nRoots = %d x1 = %g x2 = %g", answer_nRoots, answer_x1, answer_x2);
    }
    ResetTextAttributes();
    printf("\n");
}

int RunTest() {
    printf("Testing...\n");

    FILE *testFile = fopen(TEST_FILENAME, "r");
    CleanBufferLine(testFile);

    double a = 0, b = 0, c = 0;
    RootCount nRoots = INF;
    double x1 = NAN, x2 = NAN;

    while (fscanf(testFile, "%lg %lg %lg %d %lg %lg", &a, &b, &c, (int*)&nRoots, &x1, &x2) == 6)
        TestSquareSolver(a, b, c, nRoots, x1, x2);
    
    printf("Done testing\n\n");
    return 0;
}
