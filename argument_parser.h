#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <stdlib.h>

enum ParseCode {
    PC_NO_ERROR_CONTINUE,
    PC_NO_ERROR_STOP,
    PC_ERROR_UNKNOWN_FLAG,
    PC_ERROR_WRONG_WORD_COUNT
};

struct Flag {
    const char *name;
    int nNextWords;
    const char *description;
    bool (*func)(char *args[], int nArgs);
};

ParseCode ParseFlags(char *argv[], int argc, const Flag flags[], int nFlags);
void PrintArgumentInfo(const Flag flags[], int nFlags);

#endif
