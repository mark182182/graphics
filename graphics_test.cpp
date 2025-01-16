#include "graphics_test.h"
#include <cassert>
#include <raylib.h>

int main() {

  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Graphics example");
  SetTargetFPS(60);

  // load any long living resources here

  Font font =
      LoadFontEx("resources/fonts/firacode/FiraCode-Retina.ttf", 32, 0, 250);

  SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

  char *text = "La Baguette";
  Vector2 textPosition = {screenWidth / 2 -
                              MeasureTextEx(font, text, 32, 0).x / 2,
                          screenHeight / 2 - 32 / 2};

  while (!WindowShouldClose()) {
    // update variables here

    ShowCursor();

    Vector2 cursorPosition = GetMousePosition();
    // draw
    BeginDrawing();
    ClearBackground(WHITE);
    DrawTextEx(font, text, textPosition, 32, 0, BLACK);
    DrawRectangle(cursorPosition.x, cursorPosition.y, 20, 20, RED);
    EndDrawing();
  }

  _CrtDumpMemoryLeaks();
  return 0;
}
