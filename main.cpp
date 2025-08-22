#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "square_solver.h"
#include "double_comparator.h"

int readIn(double *a, double *b, double *c);
int readOneDouble(const char* name, double *ptr);
void writeOut(RootCount root_count, double x1, double x2);

int main() {
    double a = NAN, b = NAN, c = NAN;
    if (readIn(&a, &b, &c) != 0)
        return -1;

    printf("Solving...\n");

    double x1 = NAN, x2 = NAN;
    const RootCount root_count = solveSquareEquation(a, b, c, &x1, &x2);
    writeOut(root_count, x1, x2);
}

int readOneDouble(const char* name, double *const ptr) {
    assert(ptr != NULL);
    
    printf("Enter %s: ", name);
    char separator_char = 0;
    if (scanf("%lf%c", ptr, &separator_char) != 2 || separator_char != '\n')
        return -1;
    
    return 0;
}

int readIn(double *const a, double *const b, double *const c) {
    assert( (a != b) && (b != c) && (a != c) );

    printf("ax^2 + bx + c = 0\n");
    
    if (
        readOneDouble("a", a) != 0 ||
        readOneDouble("b", b) != 0 ||
        readOneDouble("c", c) != 0
    ) {
        printf("Wrong input\n");
        return -1;
    }
    return 0;
}

void writeOut(RootCount root_count, double x1, double x2) {
    if (isZero(x1)) x1 = 0;
    if (isZero(x2)) x2 = 0;

    if (root_count == TWO && isEqual(x1, x2))
        root_count = ONE;

    switch (root_count) {
        case INF:
            printf("x is any real number\n");
            break;
        case ZERO:
            printf("x is not real number\n");
            break;
        case ONE:
            assert(!isnan(x1));
            printf("x = %g\n", x1);
            break;
        case TWO:
            assert(!isnan(x1) && !isnan(x2));
            printf("x1 = %g\n", x1);
            printf("x2 = %g\n", x2);
            break;
        default:
            assert(0);
            break;
    }
}
