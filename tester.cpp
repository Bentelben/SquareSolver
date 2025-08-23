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
        {NAN, NAN, NAN, INF, NAN, NAN}
    };


    for (int i = 0; !isnan(tests[i].a); i++) {
        double x1 = 0, x2 = 0;
        RootCount nRoots = solveSquareEquation(tests[i].a, tests[i].b, tests[i].c, &x1, &x2);
        if ( !(nRoots == tests[i].nRoots && isEqual(tests[i].x1, x1) && isEqual(tests[i].x2, x2)) ) {
            printf("Wrong answer!\n");
            printf("a = %g b = %g c = %g\n", tests[i].a, tests[i].b, tests[i].c);
            printf("got answer nRoots = %d x1 = %g x2 = %g\n", nRoots, x1, x2);
            printf("should be  nRoots = %d x1 = %g x2 = %g\n\n", tests[i].nRoots, tests[i].x1, tests[i].x2);
            return -1;
        }
    }

    printf("Done testing\n\n");
    return 0;
}


