#ifndef CCOMPLEX_H
#define CCOMPLEX_H

#include <stdio.h>

struct ccomplex {
    double real;
    double imag;
};

//! Prints complex number to stream
//!
//! @param[in] stream Destination stream
//! @param[in] value  Complex number
void FPrintComplex(FILE *stream, ccomplex value);

//! Prints complex number to stdout
//!
//! @param[in] value  Complex number
//!
//! @note Equivalent to `FPrintComplex(stdout, value)`
void PrintComplex(ccomplex value);

//! Scans complex number from stream
//!
//! @param[in]  stream     Source stream
//! @param[out] resulValue Pointer for complex number to put in
//!
//! @return One on success, zero on failure and EOF when end of stream reached
int FScanComplex(FILE *stream , ccomplex *resultValue);

//! Scans complex number from stdin
//!
//! @param[out] resultValue Pointer for complex number to put in
//!
//! @return One on success, zero on failure and EOF when end of stream reached
//!
//! @note Equivalent to `FScanComplex(stdin, resultValue)`
int ScanComplex(ccomplex *resultValue);

//! Determines if two complex numbers are equal
//! 
//! @param[in]  value1 First complex number
//! @param[out] value2 Second complex number
//!
//! @return True if numbers are equal and false in other cases
bool IsComplexEqual(ccomplex value1, ccomplex value2);

//! Determines if complex number is zero
//! 
//! @param[in] value Complex number
//!
//! @return True if number is zero and false in other cases
bool IsComplexZero(ccomplex value);

//! Determines if complex number is NAN
//! 
//! @param[in] value Complex number
//!
//! @return True if number is NAN and false in other cases
bool IsComplexNan(ccomplex value);

//! Forces number to be zero if it is very close to it
//! 
//! @param[out] value Complex number
void ZeroizeComplex(ccomplex *value);

//! Calculates norm of complex number
//!
//! @param[in] value Complex number
//!
//! @return Norm of this number
double getComplexNorm(ccomplex value);

//! Calculates angle of complex number
//!
//! @param[in] value Complex number
//!
//! @return Angle of this number
double getComplexAngle(ccomplex value);

//! Calculates square root of complex number
//!
//! @param[in] value Complex number
//!
//! @return Square root of this number
ccomplex ComplexSqrt(ccomplex value);

//! Multiplies two complex numbers
//!
//! @param[in] value1 First value
//! @param[in] value2 Second value
//!
//! @return Product of these numbers
ccomplex ComplexMultiply(ccomplex value1, ccomplex value2);

//! Divides two complex numbers
//!
//! @param[in] divident Divident value
//! @param[in] divider Divider value
//!
//! @return Quotient of these numbers
ccomplex ComplexDivide(ccomplex divident, ccomplex divider);

//! Adds two complex numbers
//!
//! @param[in] value1 First value
//! @param[in] value2 Second value
//!
//! @return Sum of theese numbers
ccomplex ComplexAdd(ccomplex value1, ccomplex value2);

//! Subtracts two complex numbers
//!
//! @param[in] value1 First value
//! @param[in] value2 Second value
//!
//! @return Difference of theese numbers
ccomplex ComplexSubtract(ccomplex value1, ccomplex value2);

#endif
