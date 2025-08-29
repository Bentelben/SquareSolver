#include "square_solver.h"

#include <math.h>

#include "utils/myassert.h"
#include "utils/ccomplex.h"
#include "utils/double_comparator.h"

static const ccomplex COMPLEX_FOUR =      {.real =  4, .imag = 0};
static const ccomplex COMPLEX_TWO =       {.real =  2, .imag = 0};
static const ccomplex COMPLEX_MINUS_ONE = {.real = -1, .imag = 0};

static RootCount SolveLinear(const ccomplex b, const ccomplex c, ccomplex *const x) {
    myassert(x, "Ptr for out value is NULL");

    if (IsComplexZero(b)) {
        if (IsComplexZero(c))
            return RC_INF;
        else
            return RC_ZERO;
    }
    *x = ComplexDivide(
        ComplexMultiply(COMPLEX_MINUS_ONE, c),
        b
    );
    return RC_ONE;
}

RootCount SolveSquareEquation(
    const ccomplex a, const ccomplex b, const ccomplex c, ccomplex *const x1, ccomplex *const x2,
    const bool isComplex
) {
    myassert(!IsComplexNan(a), "Coefficeint a is NAN");
    myassert(!IsComplexNan(b), "Coefficeint b is NAN");
    myassert(!IsComplexNan(c), "Coefficeint c is NAN");
    myassert(x1, "Ptr for out value is NULL");
    myassert(x2, "Ptr for out value is NULL");
    myassert(x1 != x2, "Ptrs for out values are equal");

    if (IsComplexZero(a))
        return SolveLinear(b, c, x1);

    const ccomplex discriminant = ComplexSubtract(
        ComplexMultiply(b, b),
        ComplexMultiply(COMPLEX_FOUR, ComplexMultiply(a, c))
    );
    if (!isComplex && discriminant.real < 0)
        return RC_ZERO;

    const ccomplex discriminant_root = ComplexSqrt(discriminant);
    
    if (IsComplexZero(discriminant_root)) {
        *x1 = ComplexDivide(
            ComplexMultiply(COMPLEX_MINUS_ONE, b),
            ComplexMultiply(COMPLEX_TWO, a)
        );
        return RC_ONE;
    } else {
        *x1 = ComplexDivide(
            ComplexSubtract(
                ComplexMultiply(COMPLEX_MINUS_ONE, b),
                discriminant_root
            ),
            ComplexMultiply(COMPLEX_TWO, a)
        );
        *x2 = ComplexDivide(
            ComplexAdd(
                ComplexMultiply(COMPLEX_MINUS_ONE, b),
                discriminant_root
            ),
            ComplexMultiply(COMPLEX_TWO, a)
        );
        return RC_TWO;
    }
    return RC_ZERO;
}

void PrintRoots(RootCount nRoots, ccomplex x1, ccomplex x2) {
    ZeroizeComplex(&x1);
    ZeroizeComplex(&x2);

    if (nRoots == RC_TWO && IsComplexEqual(x1, x2))
        nRoots = RC_ONE;

    switch (nRoots) {
        case RC_INF:
            printf("x is any real number\n");
            break;
        case RC_ZERO:
            printf("x is not real number\n");
            break;
        case RC_ONE:
            myassert(!IsComplexNan(x1), "");
            printf("x = ");
            PrintComplex(x1);
            printf("\n");
            break;
        case RC_TWO:
            myassert(!IsComplexNan(x1) && !IsComplexNan(x2), "");
            printf("x1 = ");
            PrintComplex(x1);
            printf("\n");

            printf("x2 = ");
            PrintComplex(x2);
            printf("\n");
            break;
        default:
            myassert(0, "");
            break;
    }
}
