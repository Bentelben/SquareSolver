#include <math.h>

#include "double_comparator.h"

static const double EPS = 1e-14;

//! Test if two values are equal
//!
//! @param[in] a First value
//! @param[in] b Second value
//!
//! @return True if equal and false in other cases
bool isEqual(const double value1, const double value2) {
    return fabs(value1 - value2) < EPS;
}

//! Test if value is zero
//!
//! @param[in] x Value
//!
//! @return True if x is zero and false in other cases
bool isZero(const double value) {
    return isEqual(value, 0);
}
