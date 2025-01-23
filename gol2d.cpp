#include "gol2d.hpp"
#include "const.hpp"
#include <raylib.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <immintrin.h>

namespace Gol2d {

void CellDict::initArraysSizeBasedOnScreenSize() {
  const int screenWidth = GetScreenWidth();
  const int screenHeight = GetScreenHeight();
  const int cellCount =
      screenWidth * screenHeight / (CELL_HEIGHT_SIZE * CELL_WIDTH_SIZE);
  this->cellCount = cellCount;

  Cell **cells = new Cell *[cellCount];
  Color **colors = new Color *[cellCount];

  for (int i = 0; i < cellCount; i++) {
    Cell *cell = new Cell;
    cells[i] = cell;

    Color *color = new Color;
    colors[i] = color;
  }

  this->cells = cells;

  int *positionsX = new int[cellCount];
  this->positionsX = positionsX;

  int *positionsY = new int[cellCount];
  this->positionsY = positionsY;

  this->colors = colors;
}

void CellDict::freeArrays() {
  if (this->cells != nullptr && this->cells[0] != nullptr) {
    for (int i = 0; i < this->cellCount; i++) {
      delete this->cells[i];
      delete this->colors[i];
    }
  }
}

/*
Generate random values for each array
*/
CellDict *Generator::initializeCells(CellDict *cd) {
  int i = 0;
  for (int posX = 0; posX < GetScreenWidth(); posX += +CELL_WIDTH_SIZE) {
    for (int posY = 0; posY < GetScreenHeight(); posY += CELL_HEIGHT_SIZE) {
      cd->cells[i]->is_alive = {std::rand() % INITIAL_FREQUENCY == 0};
      cd->positionsX[i] = posX;
      cd->positionsY[i] = posY;
      cd->colors[i]->r = std::rand() + 255;
      cd->colors[i]->g = std::rand() + 255;
      cd->colors[i]->b = std::rand() + 255;
      cd->colors[i]->a = 255;
      i++;
    }
  }
  return cd;
}

/*
Ruleset (brought to you by wikipedia:
https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life): Any live cell with fewer
than two live neighbours dies, as if by underpopulation. Any live cell with two
or three live neighbours lives on to the next generation. Any live cell with
more than three live neighbours dies, as if by overpopulation. Any dead cell
with exactly three live neighbours becomes a live cell, as if by reproduction.
*/
CellDict *Generator::iterateCells(CellDict *cd) {
  // TODO here we do the iteration based on the ruleset
  return NULL;
}

void Generator::checkNeightbours(CellDict *cd) {
  for (int i = 0; i < sizeof(cd->cells); i++) {
    // check neightbours
  }
}
} // namespace Gol2d
