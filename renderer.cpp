#include "renderer.hpp"
#include "font.hpp"
#include "gol2d.hpp"

#include <cassert>
#include <raylib.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include "const.hpp"

void Renderer::render() {
  InitWindow(Const::SCREEN_WIDTH, Const::SCREEN_HEIGHT, "Graphics example");

  // load any long living resources here
  DisplayFont::FontDict *fd = DisplayFont::loadFonts();
  Font *firaCodeFont = getFontByName(fd, "FiraCode-Retina");

  bool isWireframeMode = false;
  int pressed = 0;
  bool isPaused = false;
  float renderSpeed = 0.2;
  float deltaTime = 0;
  int fpsCap = 60;
  SetTargetFPS(fpsCap);

  Gol2d::CellsToDrawSOA *cd = new Gol2d::CellsToDrawSOA;
  Gol2d::Generator::initArraysBasedOnCellSize(cd);
  Gol2d::Generator::initializeCells(cd);
  Gol2d::CellsToDrawSOA *previousCd = nullptr;

  while (!WindowShouldClose() && pressed != 'q') {
    ClearBackground(WHITE);

    // update variables here
    Vector2 cursorPosition = GetMousePosition();
    pressed = GetCharPressed();

    if (fpsCap == 60 && pressed == 'c') {
      fpsCap = 0;
      SetTargetFPS(fpsCap);
    } else if (fpsCap == 0 && pressed == 'c') {
      fpsCap = 60;
      SetTargetFPS(fpsCap);
    }

    if (!isWireframeMode && pressed == 't') {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      isWireframeMode = true;
    } else if (isWireframeMode && pressed == 't') {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      isWireframeMode = false;
    }

    BeginDrawing();
    HideCursor();

    if (pressed == 'r') {
      Gol2d::Generator::initializeCells(cd);
    }

    if (pressed == 'p') {
      isPaused = !isPaused;
    }

    if (pressed == 'w') {
      renderSpeed -= 0.1;
    }

    if (pressed == 's') {
      renderSpeed += 0.1;
    }

    if (isPaused == 0 && deltaTime >= renderSpeed) {
      auto a = clock();
      // before the next generation, we have to make a copy of the first,
      // generation to check the neighbours
      previousCd = Gol2d::Generator::deepCopyCells(cd);
      Gol2d::Generator::nextGeneration(cd, previousCd);
      std::cout << "nextGeneration ticks: " << clock() - a << std::endl;
      deltaTime = 0;
    }
    deltaTime += GetFrameTime();

    for (int i = 0; i < Gol2d::CELL_COUNT; i++) {
      if ((&cd->cells[i])->is_alive) {
        DrawRectangle(cd->positionsX[i], cd->positionsY[i],
                      Gol2d::CELL_HEIGHT_RATIO, Gol2d::CELL_WIDTH_RATIO,
                      *cd->colors[i]);
      }
    }

    DrawTextEx(*firaCodeFont, "\u2714", cursorPosition, 32, 0, BLACK);
    DrawTextEx(*firaCodeFont, ("FPS: " + std::to_string(GetFPS())).c_str(),
               Vector2{10, 10}, 32, 0, RED);
    DrawTextEx(*firaCodeFont,
               ("Frametime: " + std::to_string(GetFrameTime()) + " ms").c_str(),
               Vector2{10, 40}, 32, 0, RED);
    DrawTextEx(*firaCodeFont, "Press 't' for wireframe mode", Vector2{10, 70},
               32, 0, RED);
    DrawTextEx(*firaCodeFont, "Press 'q' to quit", Vector2{10, 110}, 32, 0,
               RED);
    EndDrawing();

    // free objects after each frame
  }

  // free any objects that are long living, but don't need to be present on
  // every frame
  Gol2d::Generator::freeArrays(cd);
}