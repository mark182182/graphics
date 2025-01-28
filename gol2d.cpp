#include "gol2d.hpp"
#include "const.hpp"
#include <raylib.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <immintrin.h>
#include <thread>

namespace Gol2d {

void Generator::initArraysBasedOnCellSize(CellsToDrawSOA *cd) {
  Cell **cells = new Cell *[CELL_COUNT];

  for (int i = 0; i < CELL_COUNT; i++) {
    Cell *cell = new Cell;
    cells[i] = cell;
  }

  cd->cells = cells;

  int *positionsX = new int[CELL_COUNT];
  cd->positionsX = positionsX;

  int *positionsY = new int[CELL_COUNT];
  cd->positionsY = positionsY;

  Color **colors = new Color *[CELL_COUNT];
  cd->colors = colors;
}

void Generator::freeArrays(CellsToDrawSOA *cd) {
  if (cd->cells != nullptr && cd->cells[0] != nullptr) {
    for (int i = 0; i < CELL_COUNT; i++) {
      delete cd->cells[i];
    }
    delete[] cd->cells;
  }
}

void Generator::initializeCells(CellsToDrawSOA *cd) {
  int i = 0;
  for (int posX = 0; posX < Const::SCREEN_WIDTH; posX += CELL_WIDTH_RATIO) {
    for (int posY = 0; posY < Const::SCREEN_HEIGHT; posY += CELL_HEIGHT_RATIO) {
      bool is_alive = std::rand() % INITIAL_FREQUENCY == 0;
      cd->cells[i]->is_alive = is_alive;
      cd->positionsX[i] = posX;
      cd->positionsY[i] = posY;
      cd->colors[i] = &Const::RANDOM_COLORS[std::rand() % 20];
      i++;
    }
  }
}

CellsToDrawSOA *Generator::deepCopyCells(CellsToDrawSOA *originalCd) {
  Gol2d::CellsToDrawSOA *newCd = new Gol2d::CellsToDrawSOA;
  Gol2d::Generator::initArraysBasedOnCellSize(newCd);

  Cell **newCells = new Cell *[CELL_COUNT];

  for (int i = 0; i < CELL_COUNT; i++) {
    Cell *cell = new Cell;
    cell->is_alive = originalCd->cells[i]->is_alive;
    newCells[i] = cell;
  }

  newCd->cells = newCells;
  return newCd;
}

void Generator::nextGeneration(CellsToDrawSOA *cd, CellsToDrawSOA *previousCd) {

  for (int i = 0; i < CELL_COUNT; i++) {
    int neighbours = checkNeighbours(previousCd, i);
    // under or overpopulation
    if (neighbours < 2 || neighbours > 3) {
      cd->cells[i]->is_alive = false;
      // reproduction
    } else if (!cd->cells[i]->is_alive && neighbours == 3) {
      cd->cells[i]->is_alive = true;
    }
  }
  // TODO: previousCd is not needed anymore, can be freed, but currently there
  // is a memory leak
  //freeArrays(previousCd);
  //delete previousCd;
}

int Generator::checkNeighbours(CellsToDrawSOA *previousCd, int i) {
  int neighbours = 0;

  // TODO: does not work for some reason
  for (int diagIdx : DIAGONAL_INDEXES) {
    int relativeDiagIdx = diagIdx + i;
    if (relativeDiagIdx >= 0 && relativeDiagIdx <= (CELL_COUNT - 1) &&
        previousCd->cells[relativeDiagIdx]->is_alive) {
      // the relative diagonal cell
      neighbours++;
    }
  }

  // TODO: does not work for some reason
  for (int adjIdx : ADJECENT_INDEXES) {
    int relativeAdjIdx = adjIdx + i;
    if (relativeAdjIdx >= 0 && relativeAdjIdx <= (CELL_COUNT - 1) &&
        previousCd->cells[relativeAdjIdx]->is_alive) {
      // the adjecent diagonal cell
      neighbours++;
    }
  }

  return neighbours;
}

} // namespace Gol2d
