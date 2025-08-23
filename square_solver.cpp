#include <math.h>
#include <assert.h>

#include "square_solver.h"
#include "double_comparator.h"

static RootCount solveLinear(const double b, const double c, double *const x) {
    if (isZero(b)) {
        if (isZero(c))
            return INF;
        else
            return ZERO;
    }
    *x = -c/b;
    return ONE;
}

RootCount solveSquareEquation(const double a, const double b, const double c, double *const x1, double *const x2) {
    assert(!isnan(a));
    assert(!isnan(b));
    assert(!isnan(c));
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (isZero(a))
        return solveLinear(b, c, x1);

    const double discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return ZERO;
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
