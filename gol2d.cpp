#include "gol2d.hpp"
#include "const.hpp"
#include <raylib.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <immintrin.h>
#include <map>
#include <string>

namespace Gol2d {

void Generator::initArraysSizeBasedOnScreenSize(CellsToDrawSOA *cd) {
  const int screenWidth = GetScreenWidth();
  const int screenHeight = GetScreenHeight();
  const int cellCount =
      screenWidth * screenHeight / (CELL_HEIGHT_SIZE * CELL_WIDTH_SIZE);
  cd->cellCount = cellCount;

  Cell **cells = new Cell *[cellCount];

  for (int i = 0; i < cellCount; i++) {
    Cell *cell = new Cell;
    cells[i] = cell;
  }

  cd->cells = cells;

  int *positionsX = new int[cellCount];
  cd->positionsX = positionsX;

  int *positionsY = new int[cellCount];
  cd->positionsY = positionsY;

  Color **colors = new Color *[cellCount];
  cd->colors = colors;

  std::unordered_map<std::string, bool> *cellAliveByXY =
      new std::unordered_map<std::string, bool>;
  cellAliveByXY = {};
  cd->cellAliveByXY = cellAliveByXY;
}

void Generator::freeArrays(CellsToDrawSOA *cd) {
  if (cd->cells != nullptr && cd->cells[0] != nullptr) {
    for (int i = 0; i < cd->cellCount; i++) {
      delete cd->cells[i];
    }
    cd->cellAliveByXY->clear();
    delete cd->cellAliveByXY;
  }
}

void Generator::initializeCells(CellsToDrawSOA *cd) {
  int i = 0;
  for (int posX = 0; posX < GetScreenWidth(); posX += CELL_WIDTH_SIZE) {

    for (int posY = 0; posY < GetScreenHeight(); posY += CELL_HEIGHT_SIZE) {
      bool is_alive = std::rand() % INITIAL_FREQUENCY == 0;
      cd->cells[i]->is_alive = is_alive;
      cd->positionsX[i] = posX;
      cd->positionsY[i] = posY;

      std::string lookupKey = std::to_string(posX) + "," + std::to_string(posY);
      (*cd->cellAliveByXY)[lookupKey] = is_alive;
      cd->colors[i] = &Const::RANDOM_COLORS[std::rand() % 20];
      i++;
    }
  }
}

CellsToDrawSOA *Generator::deepCopy(CellsToDrawSOA *originalCd) {
  Gol2d::CellsToDrawSOA *newCd = new Gol2d::CellsToDrawSOA;
  Gol2d::Generator::initArraysSizeBasedOnScreenSize(newCd);

  int cellCount = originalCd->cellCount;
  newCd->cellCount = cellCount;

  Cell **newCells = new Cell *[cellCount];

  int *newPositionsX = new int[cellCount];
  int *newPositionsY = new int[cellCount];

  Color **newColors = new Color *[cellCount];

  for (int i = 0; i < cellCount; i++) {

    Cell *cell = new Cell;
    cell->is_alive = originalCd->cells[i]->is_alive;
    newCells[i] = cell;

    newPositionsX[i] = originalCd->positionsX[i];
    newPositionsY[i] = originalCd->positionsY[i];
    newColors[i] = originalCd->colors[i];
  }

  newCd->cells = newCells;
  newCd->positionsX = newPositionsX;
  newCd->positionsY = newPositionsY;
  newCd->colors = newColors;

  std::unordered_map<std::string, bool> newCellAliveByXY = {};

  for (auto i : *originalCd->cellAliveByXY) {
    newCellAliveByXY[i.first] = *originalCd->cellAliveByXY[i.first];
  }

  newCd->cellAliveByXY = &newCellAliveByXY;

  return newCd;
}

void Generator::nextGeneration(CellsToDrawSOA *cd, CellsToDrawSOA *previousCd) {

  for (int i = 0; i < cd->cellCount; i++) {
    int neighbours = checkNeighbours(previousCd, previousCd->positionsX[i],
                                     previousCd->positionsY[i]);
    std::string lookupKey = std::to_string(cd->positionsX[i]) + "," +
                            std::to_string(cd->positionsY[i]);

    // under or overpopulation
    if (neighbours < 2 || neighbours > 3) {
      cd->cells[i]->is_alive = false;
      (*cd->cellAliveByXY)[lookupKey] = false;
      // reproduction
    } else if (!cd->cells[i]->is_alive && neighbours == 3) {
      cd->cells[i]->is_alive = true;
      (*cd->cellAliveByXY)[lookupKey] = true;
    }
  }
}

int Generator::checkNeighbours(CellsToDrawSOA *cd, int cellPosX, int cellPosY) {
  // TODO: use SIMD instead

  int diagVecX1 = cellPosX + (DIAGONALS[0].x * CELL_WIDTH_SIZE);
  int diagVecY1 = cellPosY + (DIAGONALS[0].y * CELL_HEIGHT_SIZE);

  int diagVecX2 = cellPosX + (DIAGONALS[1].x * CELL_WIDTH_SIZE);
  int diagVecY2 = cellPosY + (DIAGONALS[1].y * CELL_HEIGHT_SIZE);

  int diagVecX3 = cellPosX + (DIAGONALS[2].x * CELL_WIDTH_SIZE);
  int diagVecY3 = cellPosY + (DIAGONALS[2].y * CELL_HEIGHT_SIZE);

  int diagVecX4 = cellPosX + (DIAGONALS[3].x * CELL_WIDTH_SIZE);
  int diagVecY4 = cellPosY + (DIAGONALS[3].y * CELL_HEIGHT_SIZE);

  int adjVecX1 = cellPosX + (ADJECENTS[0].x * CELL_WIDTH_SIZE);
  int adjVecY1 = cellPosY + (ADJECENTS[0].y * CELL_HEIGHT_SIZE);

  int adjVecX2 = cellPosX + (ADJECENTS[1].x * CELL_WIDTH_SIZE);
  int adjVecY2 = cellPosY + (ADJECENTS[1].y * CELL_HEIGHT_SIZE);

  int adjVecX3 = cellPosX + (ADJECENTS[2].x * CELL_WIDTH_SIZE);
  int adjVecY3 = cellPosY + (ADJECENTS[2].y * CELL_HEIGHT_SIZE);

  int adjVecX4 = cellPosX + (ADJECENTS[3].x * CELL_WIDTH_SIZE);
  int adjVecY4 = cellPosY + (ADJECENTS[3].y * CELL_HEIGHT_SIZE);

  int neighbours = 0;

  addNeighbourIfPresent(cd, diagVecX1, diagVecY1, &neighbours);
  addNeighbourIfPresent(cd, diagVecX2, diagVecY2, &neighbours);
  addNeighbourIfPresent(cd, diagVecX3, diagVecY3, &neighbours);
  addNeighbourIfPresent(cd, diagVecX4, diagVecY4, &neighbours);
  addNeighbourIfPresent(cd, adjVecX1, adjVecY1, &neighbours);
  addNeighbourIfPresent(cd, adjVecX2, adjVecY2, &neighbours);
  addNeighbourIfPresent(cd, adjVecX3, adjVecY3, &neighbours);
  addNeighbourIfPresent(cd, adjVecX4, adjVecY4, &neighbours);

  return neighbours;
}

void Generator::addNeighbourIfPresent(CellsToDrawSOA *cd, int checkPosX,
                                      int checkPosY, int *neigbours) {
  std::string lookupKey =
      std::to_string(checkPosX) + "," + std::to_string(checkPosY);
  if ((*cd->cellAliveByXY)[lookupKey]) {
    (*neigbours)++;
  }
}
} // namespace Gol2d
