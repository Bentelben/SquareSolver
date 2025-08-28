#include "myassert.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "../io/display_controller.h"

static void printRedLine(size_t length) {
    FSetColor(stderr, RED, NORMAL, BACKGROUND);
    for (size_t i = 0; i < length; i++) fprintf(stderr, "-");
    FResetTextAttributes(stderr);
    fprintf(stderr, "\n");
}

void _myassert(const char *filename, const int line, const char *func, const char *stringStatement, const bool statement, const char *format...) {
    if (statement) return;

    va_list va_args;
    va_start(va_args, statement);

    printRedLine(40);
    FSetColor(stderr, RED, NORMAL, FOREGROUND);
    fprintf(stderr, 
            "%s:%d in function `%s`\n"
           "Assertion failed: `%s`\n", filename, line, func, stringStatement);
    FSetColor(stderr, CYAN, NORMAL, FOREGROUND);
    vfprintf(stderr, format, va_args);
    fprintf(stderr, "\n");
    printRedLine(40);
    va_end(va_args);

    abort();
}
