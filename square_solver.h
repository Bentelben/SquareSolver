#ifndef SQUARE_SOLVER_H
#define SQUARE_SOLVER_H

enum RootCount {ZERO, ONE, TWO, INF};

RootCount solveSquareEquation(double a, double b, double c, double *x1, double *x2);

#endif
