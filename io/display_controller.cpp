#include "display_controller.h"

#include <stdio.h>

#include "../utils/myassert.h"

static const char *const ESCAPE_STRING = "\033[";
static const char *const SEPARATOR_STRING = ";";
static const char *const CLOSING_STRING = "m";

static void FPrintControlSequence(FILE *stream, const int n, const int m) {
    myassert(stream, "Ptr to stream is NULL");
    fprintf(stream, "%s%d%s%d%s", ESCAPE_STRING, n, SEPARATOR_STRING, m, CLOSING_STRING);
}

void FSetColor(FILE *stream, const Color color, const ColorBrightness brightness, const ColorType type) {
    myassert(stream, "Ptr to stream is NULL");
    const int code = (int)color + (int)brightness + (int)type;
    FPrintControlSequence(stream, 0, code);
};

void SetColor(const Color color, const ColorBrightness brightness, const ColorType type) {
    FSetColor(stdout, color, brightness, type);
}

void FResetTextAttributes(FILE *stream) {
    myassert(stream, "Ptr to stream is NULL");
    FPrintControlSequence(stream, 0, 0);
}

void ResetTextAttributes() {
    FResetTextAttributes(stdout);
}
