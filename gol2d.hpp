#ifndef GOL2D_H
#define GOL2D_H

#include <raylib.h>

namespace Gol2d {
const int CELL_HEIGHT_SIZE = 5;
const int CELL_WIDTH_SIZE = 5;
const int INITIAL_FREQUENCY = 20;

typedef struct Cell {
  bool is_alive; // populated or unpopulated
} Cell;

typedef struct CellsToDrawSOA {
  Cell **cells;
  int *positionsX;
  int *positionsY;
  Color **colors;
  int cellCount;
  void initArraysSizeBasedOnScreenSize();
  void freeArrays();
} CellsToDrawSOA;

typedef struct Generator {
  static CellsToDrawSOA *initializeCells(CellsToDrawSOA *cd);
  static CellsToDrawSOA *iterateCells(CellsToDrawSOA *cd);

private:
  void checkNeightbours(CellsToDrawSOA *cd);
} Generator;

} // namespace Gol2d
#endif
