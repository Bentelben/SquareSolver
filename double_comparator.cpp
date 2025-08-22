#include <math.h>

#include "double_comparator.h"

static const double EPS = 1e-14;

//! Test if two values are equal
//!
//! @param[in] a First value
//! @param[in] b Second value
//!
//! @return True if equal and false in other cases
bool isEqual(const double a, const double b) {
    return fabs(a - b) < EPS;
}

//! Test if value is zero
//!
//! @param[in] x Value
//!
//! @return True if x is zero and false in other cases
bool isZero(const double x) {
    return isEqual(x, 0);
}
