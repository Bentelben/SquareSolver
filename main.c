#include <stdio.h>

#include "square_solver.h"

#define WRONG_INPUT_MESSAGE "Wrong input\n"

int main(void) {
    double A, B, C;
    
    printf("Ax^2 + Bx + C = 0\n");
    printf("Enter A, B and C:\n");
    if (scanf("%lf %lf %lf", &A, &B, &C) != 3) {
        printf(WRONG_INPUT_MESSAGE);
        return -1;
    }
    printf("Solving...\n");

    double x1, x2;
    signed char count = solveSquareEquation(A, B, C, &x1, &x2);
    if (count == -1) {
        printf("x is any real number");
    } else if (count == 0) {
        printf("x is not real number");
    } else if (count == 1) {
        printf("x = %lf", x1);
    } else if (count == 2) {
        printf("x1 = %lf\nx2 = %lf", x1, x2);
    } else {
        printf("Some error\n");
        return -2;
    }
    printf("\n");
    return 0;
}
