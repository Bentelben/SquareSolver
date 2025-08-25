#include "square_solver.h"
#include "utils/double_comparator.h"

#include <math.h>
#include <assert.h>

static RootCount SolveLinear(const double b, const double c, double *const x) {
    assert(x);

    if (IsZero(b)) {
        if (IsZero(c))
            return RC_INF;
        else
            return RC_ZERO;
    }
    *x = -c/b;
    return RC_ONE;
}

RootCount SolveSquareEquation(const double a, const double b, const double c, double *const x1, double *const x2) {
    assert(!isnan(a));
    assert(!isnan(b));
    assert(!isnan(c));
    assert(x1);
    assert(x2);
    assert(x1 != x2);

    if (IsZero(a))
        return SolveLinear(b, c, x1);

    const double discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return RC_ZERO;
    const double discriminant_root = sqrt(discriminant);

    if (IsZero(discriminant_root)) {
        *x1 = -b/(2*a);
        return RC_ONE;
    } else {
        *x1 = (-b - discriminant_root)/(2*a);
        *x2 = (-b + discriminant_root)/(2*a);
        return RC_TWO;
    }
    return RC_ZERO;
}
