#ifndef SQUARE_SOLVER_HPP
#define SQUARE_SOLVER_HPP

enum RootCount {INF, ZERO, ONE, TWO};

RootCount solveSquareEquation(const double a, const double b, const double c, double *const x1, double *const x2);

#endif
