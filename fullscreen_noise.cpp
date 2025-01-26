#include "fullscreen_noise.hpp"
#include "const.hpp"
#include <raylib.h>
#include <stdlib.h>

void FullScreenNoise::render() {
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();

  int currentRenderPosX = 0;
  int currentRenderPosY = 0;

  int CELL_HEIGHT_SIZE = 5;
  int CELL_WIDTH_SIZE = 5;

  for (int posX = 0; posX < screenWidth; posX = posX + 5) {
    for (int posY = 0; posY < screenHeight; posY = posY + 5) {
      DrawRectangle(posX, posY, CELL_HEIGHT_SIZE, CELL_WIDTH_SIZE,
                    Const::RANDOM_COLORS[rand() % 20]);
    }
  }
}