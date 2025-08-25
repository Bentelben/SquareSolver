#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <stdlib.h>

enum ParseCode {
    PC_NO_ERROR,
    PC_ERROR_UNKNOWN_FLAG,
    PC_ERROR_WRONG_WORD_COUNT
};

struct Flag {
    const char *name;
    int nNextWords;
    const char *description;
    void (*func)(char *args[], int nArgs);
};

ParseCode ParseFlags(char *args[], Flag flags[], int nFlags);
void PrintArgumentInfo(Flag flags[], int nFlags);

#endif
