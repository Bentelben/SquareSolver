#ifndef BUFFER_CLEANER_H
#define BUFFER_CLEANER_H

#include <stdio.h>

//! Cleans read buffer until new line or EOF
//!
//! @param[in] stream Stream for clearing buffer
void CleanBufferLine(FILE* stream);

#endif
