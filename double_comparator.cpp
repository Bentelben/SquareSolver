#include <math.h>

#include "double_comparator.hpp"

static const double EPS = 1e-14;

bool isEqual(const double a, const double b) {
    return fabs(a - b) < EPS;
}

bool isZero(const double x) {
    return isEqual(x, 0);
}
