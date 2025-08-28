#include "buffer_cleaner.h"

#include <stdio.h>

#include "../utils/myassert.h"

void CleanBufferLine(FILE *const stream) {
    myassert(stream, "Ptr to stream is NULL");

    int c = 0;
    do {
        c = getc(stream);
    } while ( c != EOF && c != '\n');
}

void CleanBufferSpaces(FILE *const stream) {
    myassert(stream, "Ptr to stream is NULL");

    int c = 0;
    do {
        c = getc(stream);
    } while (c == ' ' || c == '\t');

    if (c != EOF) {
        int z = ungetc(c, stream);
        myassert(z, "");
    }
}

