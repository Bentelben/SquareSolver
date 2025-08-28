#include "display_controller.h"

#include <stdio.h>

static const char *const ESCAPE_STRING = "\033[";
static const char *const SEPARATOR_STRING = ";";
static const char *const CLOSING_STRING = "m";

static void FPrintControlSequence(FILE *stream, const int n, const int m) {
    fprintf(stream, "%s%d%s%d%s", ESCAPE_STRING, n, SEPARATOR_STRING, m, CLOSING_STRING);
}



void FSetColor(FILE *stream, const Color color, const ColorBrightness brightness, const ColorType type) {
    const int code = (int)color + (int)brightness + (int)type;
    FPrintControlSequence(stream, 0, code);
};

void SetColor(const Color color, const ColorBrightness brightness, const ColorType type) {
    FSetColor(stdout, color, brightness, type);
}

void FResetTextAttributes(FILE *stream) {
    FPrintControlSequence(stream, 0, 0);
}

void ResetTextAttributes() {
    FResetTextAttributes(stdout);
}
