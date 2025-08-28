#include "display_controller.h"

#include <stdio.h>

static const char *const ESCAPE_STRING = "\033[";
static const char *const SEPARATOR_STRING = ";";
static const char *const CLOSING_STRING = "m";

static void PrintControlSequence(const int n, const int m) {
    printf("%s%d%s%d%s", ESCAPE_STRING, n, SEPARATOR_STRING, m, CLOSING_STRING);
}

void SetColor(const Color color, const ColorBrightness brightness, const ColorType type) {
    const int code = (int)color + (int)brightness + (int)type;
    PrintControlSequence(0, code);
};

void ResetTextAttributes() {
    PrintControlSequence(0, 0);
}
