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
  Cell *cells = (Cell *)_mm_malloc(CELL_COUNT * sizeof(Cell),
                                   32); // allocates 32-byte aligned memory
  if (!cells) {
    throw std::bad_alloc();
  }

  for (int i = 0; i < CELL_COUNT; i++) {
    new (&cells[i]) Cell; // using placement new, as the storage is aligned
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
  if (cd->cells != nullptr) {
    _mm_free(cd->cells);
  }
}

void Generator::initializeCells(CellsToDrawSOA *cd) {
  int i = 0;
  for (int posX = 0; posX < Const::SCREEN_WIDTH; posX += CELL_WIDTH_RATIO) {
    for (int posY = 0; posY < Const::SCREEN_HEIGHT; posY += CELL_HEIGHT_RATIO) {
      bool is_alive = std::rand() % INITIAL_FREQUENCY == 0;
      (&cd->cells[i])->is_alive = is_alive;
      cd->positionsX[i] = posX;
      cd->positionsY[i] = posY;
      cd->colors[i] = &Const::RANDOM_COLORS[std::rand() % 20];
      i++;
    }
  }
}

CellsToDrawSOA *Generator::deepCopyCells(CellsToDrawSOA *originalCd) {
  Gol2d::CellsToDrawSOA *newCd = new Gol2d::CellsToDrawSOA;

  Cell *newCells = (Cell *)_mm_malloc(CELL_COUNT * sizeof(Cell), 32);
  if (!newCells) {
    throw std::bad_alloc();
  }

  for (int i = 0; i < CELL_COUNT; i++) {
    new (&newCells[i]) Cell();
    (&newCells[i])->is_alive = (&originalCd->cells[i])->is_alive;
  }

  newCd->cells = newCells;
  return newCd;
}

void Generator::nextGeneration(CellsToDrawSOA *cd, CellsToDrawSOA *previousCd) {

  for (int i = 0; i < CELL_COUNT; i++) {
    int neighbours = checkNeighbours(previousCd, i);
    // under or overpopulation
    if (neighbours < 2 || neighbours > 3) {
      (&cd->cells[i])->is_alive = false;
      // reproduction
    } else if (!(&cd->cells[i])->is_alive && neighbours == 3) {
      (&cd->cells[i])->is_alive = true;
    }
  }
  freeArrays(previousCd);
}

int Generator::checkNeighbours(CellsToDrawSOA *previousCd, int i) {
  int neighbours = 0;
  int arraySize = (CELL_COUNT - 1);

  for (int diagIdx : DIAGONAL_INDEXES) {
    int relativeDiagIdx = diagIdx + i;
    if (relativeDiagIdx >= 0 && relativeDiagIdx <= arraySize &&
        (&previousCd->cells[relativeDiagIdx])->is_alive) {
      // the relative diagonal cell
      neighbours++;
    }
  }

  for (int adjIdx : ADJECENT_INDEXES) {
    int relativeAdjIdx = adjIdx + i;
    if (relativeAdjIdx >= 0 && relativeAdjIdx <= arraySize &&
        (&previousCd->cells[relativeAdjIdx])->is_alive) {
      // the adjecent diagonal cell
      neighbours++;
    }
  }

  return neighbours;
}

} // namespace Gol2d
