#include "renderer.hpp"
#include "font.hpp"
#include "gol2d.hpp"

#include <cassert>
#include <raylib.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string>

void Generator::render() {
  const int screenWidth = 1280;
  const int screenHeight = 720;

  InitWindow(screenWidth, screenHeight, "Graphics example");
  SetTargetFPS(60);

  // load any long living resources here
  DisplayFont::FontDict *fd = DisplayFont::loadFonts();
  Font *firaCodeFont = getFontByName(fd, "FiraCode-Retina");

  bool isWireframeMode = false;
  int pressed = 0;
  float deltaTime = 0;
  Gol2d::CellDict *cd = new Gol2d::CellDict;
  // these will be the initial values
  cd = Gol2d::Generator::initializeCells(cd);

  while (!WindowShouldClose() && pressed != 'q') {
    ClearBackground(WHITE);

    // update variables here

    Vector2 cursorPosition = GetMousePosition();
    pressed = GetCharPressed();

    BeginDrawing();
    HideCursor();

    if (!isWireframeMode && pressed == 't') {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      isWireframeMode = true;
    } else if (isWireframeMode && pressed == 't') {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      isWireframeMode = false;
    }

    if (deltaTime >= 0.2) {
      cd = Gol2d::Generator::initializeCells(cd);
      deltaTime = 0;
    }
    deltaTime += GetFrameTime();

    for (int i = 0; i < sizeof(cd->cells) / sizeof(cd->cells[0]); i++) {
      if (cd->cells[i]->is_alive) {
        DrawRectangle(cd->positionsX[i], cd->positionsY[i],
                      Gol2d::CELL_HEIGHT_SIZE, Gol2d::CELL_WIDTH_SIZE,
                      *cd->colors[i]);
      }
    }

    DrawTextEx(*firaCodeFont, "[]", cursorPosition, 32, 0, BLACK);

    DrawText(std::to_string(GetFPS()).c_str(), 10, 10, 32, RED);
    DrawText(std::to_string(GetFrameTime()).c_str(), 10, 40, 32, RED);
    DrawText("Press 't' for wireframe mode", 10, 70, 32, RED);
    DrawText("Press 'q' to quit", 10, 110, 32, RED);
    EndDrawing();
  }
}