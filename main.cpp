#include <stdio.h>

#include "square_solver.hpp"

int main() {
    double a = 0, b = 0, c = 0;
    
    printf("ax^2 + bx + c = 0\n");
    printf("Enter a, b and c:\n");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("Wrong input\n");
        return -1;
    }
    printf("Solving...\n");

    double x1 = 0, x2 = 0;
    const RootCount count = solveSquareEquation(a, b, c, &x1, &x2);

    switch (count) {
        case INF:
            printf("x is any real number\n");
            break;
        case ZERO:
            printf("x is not real number\n");
            break;
        case ONE:
            printf("x = %lf\n", x1);
            break;
        case TWO:
            printf("x1 = %lf\nx2 = %lf\n", x1, x2);
            break;
        default:
            printf("Error\n");
            break;
    }
    return 0;
}
