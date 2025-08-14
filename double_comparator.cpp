#include <math.h>

#include "double_comparator.hpp"

static const double EPS = 1e-14;

bool isZero(const double x) {
    return fabs(x) < EPS;
}
