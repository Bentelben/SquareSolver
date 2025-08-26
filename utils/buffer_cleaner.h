#ifndef BUFFER_CLEANER_H
#define BUFFER_CLEANER_H

#include <stdio.h>

//! Cleans stream buffer until new line or EOF
//!
//! @param[in] stream Stream for clearing buffer
void CleanBufferLine(FILE* stream);

//! Cleans tabs and spaces from stream buffer
//!
//! @param[in] stream Stream for clearing buffer
void CleanBufferSpaces(FILE* stream);

#endif
