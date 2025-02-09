#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include <functional>

typedef struct Menu {
  void init();
  void update();
  void draw();

private:
  Font selectedFont;
  Vector2 cursorPosition;

  void drawTextInMenu(Vector2 firstTextPos, Vector2 *currentTextPos,
                      const char *textToDraw, int fontSize, Color rectColor,
                      Color textColor, std::function<void()> onCollision);

} Menu;

#endif