#include "font.hpp"
#include <raylib.h>
#include <iostream>
#include <string>

namespace DisplayFont {

std::unordered_map<FontType, Font> fontsByType = {};

/*
 * Load fonts into fontsByType
 */
void DisplayFont::loadFonts() {

  // FiraCode-Retina.ttf
  Font font =
      LoadFontEx("resources/fonts/firacode/FiraCode-Retina.ttf", 32, 0, 250);

  SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
  fontsByType[FontType::FiraCodeRetina] = font;
}

Font DisplayFont::getFont(FontType type) { return fontsByType[type]; };
} // namespace DisplayFont