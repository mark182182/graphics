#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <string>
#include <raylib.h>

namespace DisplayFont {
const unsigned int MAX_FONTS = 64;

typedef struct FontDict {
  std::string names[MAX_FONTS];
  Font fonts[MAX_FONTS];
} FontDict;

FontDict *loadFonts();

Font *getFontByName(FontDict *fd, std::string name);

} // namespace DisplayFont
#endif
