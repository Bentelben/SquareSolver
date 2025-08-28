#include "square_solver.h"
#include "utils/double_comparator.h"

#include <math.h>
#include "myassert.h"

#include "utils/ccomplex.h"

static RootCount SolveLinear(const double b, const double c, ccomplex *const x) {
    myassert(x, "Ptr for out value is NULL");

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
    myassert(!isnan(a), "Coefficeint a is NAN");
    myassert(!isnan(b), "Coefficeint b is NAN");
    myassert(!isnan(c), "Coefficeint c is NAN");
    myassert(x1, "Ptr for out value is NULL");
    myassert(x2, "Ptr for out value is NULL");
    myassert(x1 != x2, "Ptrs for out values are equal");

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
