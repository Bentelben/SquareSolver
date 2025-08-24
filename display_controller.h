#ifndef PRINTER_H
#define PRINTER_H

enum Color {
    BLACK = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

enum ColorBrightness {
    NORMAL = 0,
    BRIGHT = 60
};

enum ColorType {
    FOREGROUND = 0,
    BACKGROUND = 10
};

void SetColor(Color color, ColorBrightness brightness, ColorType type);
void ResetTextAttributes();

#endif
