#include <math.h>

#include "square_solver.h"

static const double EPS = 1e-14;

static RootCount solveLinear(double b, double c, double *x) {
    if (fabs(b) < EPS) return fabs(c) < EPS ? INF : ZERO;
    *x = -c/b;
    return ONE;
}

RootCount solveSquareEquation(double a, double b, double c, double *x1, double *x2) {
    // bx + c = 0
    if (fabs(a) < EPS) return solveLinear(b, c, x1);
    // ax^2 + c = 0
    if (fabs(b) < EPS) {
        if (fabs(c) < EPS) {
            *x1 = 0;
            return ONE;
        } else if ((c > 0) != (a > 0)) {
            *x1 = sqrt(-c/a);
            *x2 = -*x1;
            return TWO;
        } else return ZERO;
    }
    // ax^2 + bx + c = 0
    double d = b*b - 4*a*c;
    if (fabs(d) < EPS) {
        *x1 = -b/(2*a);
        return ONE;
    } else if (d < 0) {
        return ZERO;
    } else {
        d = sqrt(d);
        *x1 = (-b - d)/(2*a);
        *x2 = (-b + d)/(2*a);
        return TWO;
    }
    return ZERO;
}


