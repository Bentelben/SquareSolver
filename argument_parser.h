#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <stdlib.h>

enum ParseCode {
    PC_NO_ERROR_CONTINUE      = 0,
    PC_NO_ERROR_STOP          = 1,
    PC_ERROR_UNKNOWN_FLAG     = 2,
    PC_ERROR_WRONG_WORD_COUNT = 3
};

struct Flag {
    const char *fullName;
    const char *alias;
    int nNextWords;
    const char *description;
    bool (*func)(char *args[], int nArgs);
};

ParseCode ParseFlags(char *argv[], int argc, const Flag flags[], int nFlags);
void PrintArgumentInfo(const Flag flags[], int nFlags);

#endif
