#include <math.h>
#include <stdio.h>

#define EPS 1e-14

signed char solveLinear(double B, double C, double *x) {
    if (fabs(B) < EPS) return fabs(C) < EPS ? -1 : 0;
    *x = -C/B;
    return 1;
}

signed char solveSquareEquation(double A, double B, double C, double *x1, double *x2) {
    // Bx + C = 0
    if (fabs(A) < EPS) return solveLinear(B, C, x1);
    // Ax^2 + C = 0
    if (fabs(B) < EPS) {
        if (fabs(C) < EPS) {
            *x1 = 0;
            return 1;
        } else if ((C > 0) != (A > 0)) {
            *x1 = sqrt(-C/A);
            *x2 = -*x1;
            return 2;
        } else return 0;
    }
    // Ax^2 + Bx + C = 0
    double D = B*B - 4.*A*C;
    if (fabs(D) < EPS) {
        *x1 = -B/(2.*A);
        return 1;
    } else if (D < 0) {
        return 0;
    } else {
        D = sqrt(D);
        *x1 = (-B - D)/(2.*A);
        *x2 = (-B + D)/(2.*A);
        return 2;
    }
    return 0;
}


