#include "square_solver.h"
#include "utils/double_comparator.h"

#include <math.h>
#include <assert.h>

#include "utils/ccomplex.h"

static RootCount SolveLinear(const double b, const double c, ccomplex *const x) {
    assert(x);

    if (IsZero(b)) {
        if (IsZero(c))
            return RC_INF;
        else
            return RC_ZERO;
    }
    x->real = -c/b;
    x->imag = 0;
    return RC_ONE;
}

RootCount SolveSquareEquation(
    const double a, const double b, const double c, ccomplex *const x1, ccomplex *const x2,
    const bool isComplex
) {
    assert(!isnan(a));
    assert(!isnan(b));
    assert(!isnan(c));
    assert(x1);
    assert(x2);
    assert(x1 != x2);

    if (IsZero(a))
        return SolveLinear(b, c, x1);

    const double discriminant = b*b - 4*a*c;
    if (!isComplex && discriminant < 0)
        return RC_ZERO;
    
    const double discriminant_root = sqrt(fabs(discriminant));

    if (IsZero(discriminant_root)) {
        x1->real = -b/(2*a);
        x1->imag = 0;
        return RC_ONE;
    } else {
        if (discriminant > 0) {
            x1->real = (-b - discriminant_root)/(2*a);
            x1->imag = 0;
            
            x2->real = (-b + discriminant_root)/(2*a);
            x2->imag = 0;
        } else {
            x1->real = -b/(2*a);
            x1->imag = -discriminant_root/(2*a);

            x2->real = -b/(2*a);
            x2->imag = -(x1->imag);
        }
        return RC_TWO;
    }
    return RC_ZERO;
}
