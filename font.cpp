#include "font.hpp"
#include <raylib.h>
#include <iostream>
#include <string>

namespace DisplayFont {
/*
 * Load fonts from resources/fonts
 *
 * @return FontDict
 */
FontDict *loadFonts() {

  // FiraCode-Retina.ttf
  Font font =
      LoadFontEx("resources/fonts/firacode/FiraCode-Retina.ttf", 32, 0, 250);

  SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
  FontDict *fd = new FontDict;
  fd->fonts[0] = font;
  fd->names[0] = "FiraCode-Retina";

  return fd;
}

Font *getFontByName(FontDict *fd, std::string name) {
  for (int i = 0; i < MAX_FONTS; i++) {
    if (fd->names[i] == name) {
      return &fd->fonts[i];
    }
  }

  char FONT_NOT_FOUND_MSG[128] = {"Font not found: "};
  throw strcat_s(FONT_NOT_FOUND_MSG, sizeof FONT_NOT_FOUND_MSG, name.c_str());
}

} // namespace DisplayFont