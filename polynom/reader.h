#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <stdlib.h>
#include "../utils/ccomplex.h"

//! Reads one double coefficient
//!
//! @param[in]  coefficientName Name of coefficient
//! @param[out] resultValue     Value of parsed coefficient
//! @param[in]  isComplex       Determine if coefficient should be complex
//!
//! @return Zero on success
int ReadCoefficient(char coefficientName, ccomplex *resultValue, bool isComplex);

//! Reads coefficients for polynom of power nCoefficient-1 from stdin
//!
//! @param[out] resultCoefficients Array for coefficients
//! @param[in]  nCoefficient       Length of array
//! @param[in]  isComplex       Determine if coefficient should be complex
//!
//! @return Zero on success
int ReadNCoefficients(ccomplex *resultCoefficients, size_t nCoefficient, bool isComplex);

//! Makes attempts to read coefficients for polynom of power coefficient_count-1 from stdin
//!
//! @param[out] coefficients Array of coefficients
//! @param[in]  nCoefficient Length of array
//! @param[in]  attemptLimit Max count of attempts to read
//! @param[in]  isComplex       Determine if coefficient should be complex
//!
//! @return Zero on success
int ReadNCoefficientsWithAttempts(ccomplex *resultCoefficients, size_t nCoefficient, size_t attemptLimit, bool isComplex);

#endif
