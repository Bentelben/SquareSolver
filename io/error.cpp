#include "error.h"

#include <stdio.h>
#include <stdarg.h>

#include "display_controller.h"

void PrintError(const char *format, ...) {
    va_list vaList;
    va_start(vaList, format);

    FSetColor(stderr, RED, NORMAL, BACKGROUND);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, vaList);
    FResetTextAttributes(stderr);
    fprintf(stderr, "\n");

    va_end(vaList);
}
