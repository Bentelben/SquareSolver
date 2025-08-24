#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <stdlib.h>

//! Reads one double coefficient
//!
//! @param[in]  coefficientName Name of coefficient
//! @param[out] resultValue     Value of parsed coefficient
//!
//! @return Zero on success
int ReadCoefficient(char coefficientName, double *resultValue);

//! Reads coefficients for polynom of power nCoefficient-1 from stdin
//!
//! @param[out] resultCoefficients Array for coefficients
//! @param[in]  nCoefficient       Length of array
//!
//! @return Zero on success
int ReadNCoefficients(double *resultCoefficients, size_t nCoefficient);

//! Makes attempts to read coefficients for polynom of power coefficient_count-1 from stdin
//!
//! @param[out] coefficients Array of coefficients
//! @param[in]  nCoefficient Length of array
//! @param[in]  attemptLimit Max count of attempts to read
//!
//! @return Zero on success
int ReadNCoefficientsWithAttempts(double *resultCoefficients, size_t nCoefficient, size_t attemptLimit);

#endif
