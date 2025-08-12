#include <math.h>

#include "square_solver.h"

#define EPS 1e-14

static int solveLinear(double b, double c, double *x) {
    if (fabs(b) < EPS) return fabs(c) < EPS ? -1 : 0;
    *x = -c/b;
    return 1;
}

int solveSquareEquation(double a, double b, double c, double *x1, double *x2) {
    // bx + c = 0
    if (fabs(a) < EPS) return solveLinear(b, c, x1);
    // ax^2 + c = 0
    if (fabs(b) < EPS) {
        if (fabs(c) < EPS) {
            *x1 = 0;
            return 1;
        } else if ((c > 0) != (a > 0)) {
            *x1 = sqrt(-c/a);
            *x2 = -*x1;
            return 2;
        } else return 0;
    }
    // ax^2 + bx + c = 0
    double d = b*b - 4*a*c;
    if (fabs(d) < EPS) {
        *x1 = -b/(2*a);
        return 1;
    } else if (d < 0) {
        return 0;
    } else {
        d = sqrt(d);
        *x1 = (-b - d)/(2*a);
        *x2 = (-b + d)/(2*a);
        return 2;
    }
    return 0;
}


