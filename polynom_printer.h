#ifndef POLYNOM_PRINTER_H
#define POLYNOM_PRINTER_H

#include <stdlib.h>

char GetCoefficientName(size_t index);
void PrintLetterPolynom(size_t polynomPower);
void PrintPolynom(const double *coefficients, size_t nCoefficients);

#endif
