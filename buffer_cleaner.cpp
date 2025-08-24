#include "buffer_cleaner.h"

#include <stdio.h>

void CleanBufferLine(FILE* stream) {
    int c;
    do {
        c = getc(stream);
    } while ( c != EOF && c != '\n');
}
