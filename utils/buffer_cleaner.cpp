#include "buffer_cleaner.h"

#include <stdio.h>
#include "../myassert.h"

void CleanBufferLine(FILE* stream) {
    myassert(stream, "");

    int c = 0;
    do {
        c = getc(stream);
    } while ( c != EOF && c != '\n');
}

void CleanBufferSpaces(FILE* stream) {
    myassert(stream, "");

    int c = 0;
    do {
        c = getc(stream);
    } while (c == ' ' || c == '\t');

    if (c != EOF) {
        int z = ungetc(c, stream);
        myassert(z, "");
    }
}

