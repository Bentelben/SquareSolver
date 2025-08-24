#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <stdlib.h>

struct Flag {
    const char *name;
    int nNextWords;
    const char *description;
    void (*func)(char *args[], int nArgs);
};

int ParseFlags(char *args[], Flag flags[], int nFlags);
void PrintArgumentInfo(Flag flags[], int nFlags);

#endif
