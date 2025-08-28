#include "myassert.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "../io/display_controller.h"

static void printRedLine(size_t length) {
    SetColor(RED, NORMAL, BACKGROUND);
    for (size_t i = 0; i < length; i++) printf("-");
    ResetTextAttributes();
    printf("\n");
}

void _myassert(const char *filename, const int line, const char *func, const char *stringStatement, const bool statement, const char *format...) {
    if (statement) return;

    va_list va_args;
    va_start(va_args, statement);

    printRedLine(40);
    SetColor(RED, NORMAL, FOREGROUND);
    printf("%s:%d in function `%s`\n"
           "Assertion failed: `%s`\n", filename, line, func, stringStatement);
    SetColor(CYAN, NORMAL, FOREGROUND);
    vprintf(format, va_args);
    printf("\n");
    printRedLine(40);
    va_end(va_args);

    abort();
}
