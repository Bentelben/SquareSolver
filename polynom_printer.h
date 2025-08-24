#ifndef POLYNOM_PRINTER_H
#define POLYNOM_PRINTER_H

#include <stdlib.h>

//! Returns coefficient name for polynom
//!
//! @param[in]  index Coefficient index
//!
//! @return Coefficient name
char GetCoefficientName(size_t index);

//! Prints polynom with letter coefficients
//!
//! @param[in]  polynomPower Power of polynom
void PrintLetterPolynom(size_t polynomPower);

//! Prints polynom with specific coefficients
//!
//! @param[in] coefficients  Coefficients of polynom
//! @param[in] nCoefficients Count of coefficients
void PrintPolynom(double *coefficients, size_t nCoefficients);

#endif
