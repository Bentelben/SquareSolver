#include <math.h>

#include "double_comparator.h"

static const double EPS = 1e-14;

bool isEqual(const double value1, const double value2) {
    return fabs(value1 - value2) < EPS;
}

bool isZero(const double value) {
    return isEqual(value, 0);
}
