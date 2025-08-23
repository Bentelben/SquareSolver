#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <stdlib.h>

//! Reads coefficients for polynom  of power coefficient_count-1 from console
//!
//! @param[out] coefficients Array of coefficients
//! @param[in]  nCoefficient Length of array
//!
//! @return Zero on success and negative value on error
int ReadIn(double *coefficients, size_t nCoefficient);

#endif
