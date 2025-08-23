#include "tester.h"

#include "square_solver.h"
#include "double_comparator.h"

#include <stdio.h>
#include <math.h>

struct Test_squareSolver {
    double a, b, c;
    RootCount nRoots;
    double x1, x2;
};

static void UnitTestSquareSolver(
        const double a, const double b, const double c,
        RootCount answer_nRoots, const double answer_x1, const double answer_x2
    ) {
    double x1 = 0, x2 = 0;
    RootCount nRoots = SolveSquareEquation(a, b, c, &x1, &x2);
    if ( !(nRoots == answer_nRoots && IsEqual(x1, answer_x1) && IsEqual(x2, answer_x2)) ) {
        printf("Wrong answer!\n");
        printf("a = %g b = %g c = %g\n", a, b, c);
        printf("got answer nRoots = %d x1 = %g x2 = %g\n", nRoots, x1, x2);
        printf("should be  nRoots = %d x1 = %g x2 = %g\n\n", nRoots, answer_x1, answer_x2);
    }
}

int TestSquareSolver() {
    printf("Testing...\n");

    const Test_squareSolver tests[] = {
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
        UnitTestSquareSolver(
            tests[i].a, tests[i].b, tests[i].c,
            tests[i].nRoots, tests[i].x1, tests[i].x2
        ); 

    printf("Done testing\n\n");
    return 0;
}
