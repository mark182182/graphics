#include "gol2d.hpp"
#include "const.hpp"
#include <raylib.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>

namespace Gol2d {

void CellDict::setArraysSizeBasedOnScreenSize(CellDict *cd) {
  const int screenWidth = GetScreenWidth();
  const int screenHeight = GetScreenHeight();
  const int cellCount =
      screenWidth * screenHeight / (CELL_HEIGHT_SIZE * CELL_WIDTH_SIZE);

  if (cd->cells[0]) {
    for (int i = 0; i < cellCount; i++) {
      delete cd->cells[i];
    }
  }
}

/*
Generate random values
*/
CellDict *Generator::initializeCells(CellDict *cd) {
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();

  CellDict::setArraysSizeBasedOnScreenSize(cd);
  int i = 0;
  for (int posX = 0; posX < screenWidth; posX = posX + CELL_WIDTH_SIZE) {
    for (int posY = 0; posY < screenHeight; posY = posY + CELL_HEIGHT_SIZE) {
      Cell *cell = new Cell;
      cell->is_alive = {rand() % INITIAL_FREQUENCY == 0};
      cd->cells[i] = cell;
      cd->positionsX[i] = posX;
      cd->positionsY[i] = posY;
      cd->colors[i] = rand() % 2 == 0 ? &Const::RANDOM_COLORS[rand() % 20]
                                      : &Const::RANDOM_COLORS[rand() % 20];
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
