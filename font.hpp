#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <string>
#include <raylib.h>
#include <unordered_map>

namespace DisplayFont {

enum FontType { FiraCodeRetina };

void loadFonts();
Font getFont(FontType type);
} // namespace DisplayFont
#endif
