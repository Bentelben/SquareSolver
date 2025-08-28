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


//! Changes text stdout color
//!
//! @param[in] color      Color of text
//! @param[in] brightness Brightness of color
//! @param[in] type       Foregound/background
void SetColor(Color color, ColorBrightness brightness, ColorType type);

//! Resets all text attributes (include color) in stdout
void ResetTextAttributes();

#endif
