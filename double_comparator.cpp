#include "double_comparator.hpp"

static const double EPS = 1e-14;

int isZero(const double x) {
    return -EPS < x && x < EPS;
}
