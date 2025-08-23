#include <math.h>

#include "double_comparator.h"

static const double EPS = 1e-14;

bool IsEqual(const double value1, const double value2) {
    return fabs(value1 - value2) < EPS;
}

bool IsZero(const double value) {
    return IsEqual(value, 0);
}
