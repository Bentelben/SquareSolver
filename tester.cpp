#include <stdio.h>
#include <math.h>

#include "tester.h"

#include "double_comparator.h"
#include "square_solver.h"

struct Test_squareSolver {
    double a, b, c;
    RootCount nRoots;
    double x1, x2;
};

static void unitTestSquareSolver(double a, double b, double c, RootCount answer_nRoots, double answer_x1, double answer_x2) {
    double x1 = 0, x2 = 0;
    RootCount nRoots = solveSquareEquation(a, b, c, &x1, &x2);
    if ( !(nRoots == answer_nRoots && isEqual(x1, answer_x1) && isEqual(x2, answer_x2)) ) {
        printf("Wrong answer!\n");
        printf("a = %g b = %g c = %g\n", a, b, c);
        printf("got answer nRoots = %d x1 = %g x2 = %g\n", nRoots, x1, x2);
        printf("should be  nRoots = %d x1 = %g x2 = %g\n\n", nRoots, answer_x1, answer_x2);
    }
}

int testSquareSolver() {
    printf("Testing...\n");

    Test_squareSolver tests[] = {
        { 0,  0,  0, INF,  0,  0},
        { 1,  2,  1, ONE, -1,  0},
        { 1,  2, -3, TWO, -3,  1},
        { 1,  0,  0, ONE,  0,  0},
        {-1,  0,  0, ONE,  0,  0},
        { 0,  1,  0, ONE,  0,  0},
        { 0, -1,  0, ONE,  0,  0},
        { 0,  0,  1, ZERO, 0,  0}
    };

    for (size_t i = 0; i < sizeof(tests)/sizeof(*tests); i++)
        unitTestSquareSolver(tests[i].a, tests[i].b, tests[i].c, tests[i].nRoots, tests[i].x1, tests[i].x2); 

    printf("Done testing\n\n");
    return 0;
}


