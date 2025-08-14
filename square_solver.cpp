#include <math.h>

#include "square_solver.hpp"
#include "double_comparator.hpp"

static RootCount solveLinear(const double b, const double c, double *const x) {
    if (isZero(b)) return isZero(c) ? INF : ZERO;
    *x = -c/b;
    return ONE;
}

RootCount solveSquareEquation(const double a, const double b, const double c, double *const x1, double *const x2) {
    if (isZero(a)) return solveLinear(b, c, x1);

    const double discriminant = b*b - 4*a*c;
    if (discriminant < 0) return ZERO;
    const double discriminant_root = sqrt(discriminant);

    if (isZero(discriminant_root)) {
        *x1 = -b/(2*a);
        return ONE;
    } else {
        *x1 = (-b - discriminant_root)/(2*a);
        *x2 = (-b + discriminant_root)/(2*a);
        return TWO;
    }
    return ZERO;
}
