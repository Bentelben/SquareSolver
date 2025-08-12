#include <stdio.h>

#include "square_solver.h"

#define WRONG_INPUT_MESSAGE "Wrong input\n"

int main(void) {
    double a = 0, b = 0, c = 0;
    
    printf("ax^2 + bx + c = 0\n");
    printf("Enter a, b and c:\n");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf(WRONG_INPUT_MESSAGE);
        return -1;
    }
    printf("Solving...\n");

    double x1 = 0, x2 = 0;
    int count = solveSquareEquation(a, b, c, &x1, &x2);
    if (count == -1) {
        printf("x is any real number\n");
    } else if (count == 0) {
        printf("x is not real number\n");
    } else if (count == 1) {
        printf("x = %lf\n", x1);
    } else if (count == 2) {
        printf("x1 = %lf\nx2 = %lf\n", x1, x2);
    } else {
        printf("Some error\n");
        return -2;
    }
    return 0;
}
