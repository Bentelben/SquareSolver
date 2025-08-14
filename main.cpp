#include <stdio.h>

#include "square_solver.hpp"

int readIn(double *a, double *b, double *c);
void writeOut(RootCount root_count, double x1, double x2);

int main() {
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    if (readIn(&a, &b, &c) != 0) return -1;
    printf("Solving...\n");
    const RootCount root_count = solveSquareEquation(a, b, c, &x1, &x2);
    writeOut(root_count, x1, x2);
}

int readIn(double *const a, double *const b, double *const c) {
    printf("ax^2 + bx + c = 0\n");
    printf("Enter a, b and c:\n");
    if (scanf("%lf %lf %lf", a, b, c) != 3) {
        printf("Wrong input\n");
        return -1;
    }
    return 0;
}

void writeOut(const RootCount root_count, const double x1, const double x2) {
    switch (root_count) {
        case INF:
            printf("x is any real number\n");
            break;
        case ZERO:
            printf("x is not real number\n");
            break;
        case ONE:
            printf("x = %g\n", x1);
            break;
        case TWO:
            printf("x1 = %g\nx2 = %g\n", x1, x2);
            break;
        default:
            printf("Error\n");
            break;
    }
}
