#ifndef CCOMPLEX_H
#define CCOMPLEX_H

#include <stdio.h>

struct ccomplex {
    double real;
    double imag;
};

void FPrintComplex(FILE *stream, ccomplex value);
void PrintComplex(ccomplex value);

int FScanComplex(FILE *stream , ccomplex *resultValue);
int ScanComplex(ccomplex *resultValue);

bool IsComplexEqual(ccomplex value1, ccomplex value2);
bool IsComplexZero(ccomplex value);

bool IsComplexNan(ccomplex value);

void ZeroizeComplex(ccomplex *value);

double getComplexNorm(ccomplex value);
double getComplexAngle(ccomplex value);
ccomplex ComplexRoot(ccomplex value);
ccomplex ComplexMultiply(ccomplex value1, ccomplex value2);
ccomplex ComplexDivide(ccomplex value1, ccomplex value2);
ccomplex ComplexAdd(ccomplex value1, ccomplex value2);
ccomplex ComplexSubtract(ccomplex value1, ccomplex value2);

#endif
