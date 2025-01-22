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

typedef struct CellDict {
  Cell *cells[36864]{};
  int positionsX[36864]{};
  int positionsY[36864]{};
  Color *colors[36864]{};
  static void setArraysSizeBasedOnScreenSize(CellDict *cd);
} CellDict;

typedef struct Generator {
  static CellDict *initializeCells(CellDict *cd);
  static CellDict *iterateCells(CellDict *cd);

private:
  void checkNeightbours(CellDict *cd);
} Generator;

} // namespace Gol2d
#endif
