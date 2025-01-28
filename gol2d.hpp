#ifndef GOL2D_H
#define GOL2D_H

#include <raylib.h>
#include "const.hpp"

namespace Gol2d {
const int CELL_HEIGHT_RATIO = 1 << 3; // power of two is recommended
const int CELL_WIDTH_RATIO = 1 << 3;  // power of two is recommended
const int INITIAL_FREQUENCY = 5;

const int CELL_HEIGHT_SIZE = Const::SCREEN_HEIGHT / CELL_HEIGHT_RATIO;
const int CELL_WIDTH_SIZE = Const::SCREEN_WIDTH / CELL_WIDTH_RATIO;
const int CELL_COUNT = CELL_HEIGHT_SIZE * CELL_WIDTH_SIZE;

//
//
/*
 * Diagonals relative to the current cell, e.g. if the ratio is 10:
 * top-left  bottom-left bottom-right    top-right
 * -72 - 1   -72 + 1     +72 - 1         +72 + 1
 */
const int DIAGONAL_INDEXES[4] = {(-1 * CELL_HEIGHT_SIZE) - 1,
                                 (-1 * CELL_HEIGHT_SIZE) + 1,
                                 CELL_HEIGHT_SIZE - 1, CELL_HEIGHT_SIZE + 1};
/*
 * Adjecent relative idx to the current cell, e.g. if the ratio is 10:
 * top   bottom  left    right
 * -1    +1      -72     +72
 */
const int ADJECENT_INDEXES[4] = {-1, +1, (-1 * CELL_HEIGHT_SIZE),
                                 CELL_HEIGHT_SIZE};

typedef struct Cell {
  bool is_alive; // populated or unpopulated
} Cell;

/*
 * Container for drawing the cells. The cells are stored in height by width in
 * one continous memory block, from top to bottom.
 *
 * The actual cell values (0 or 1) represent the populated/unpopulated cells.
 *   x012
 * y ____
 * 0|1100|
 * 1|0111|
 * 2|1001|
 * ........
 */
typedef struct CellsToDrawSOA {
  Cell **cells;
  int *positionsX;
  int *positionsY;
  Color **colors;
} CellsToDrawSOA;

typedef struct Generator {
  static void initArraysBasedOnCellSize(CellsToDrawSOA *cd);
  static void freeArrays(CellsToDrawSOA *cd);

  /*
   * Creates a deep copy of the given CellsToDrawSOA and returns its pointer.
   */
  static CellsToDrawSOA *deepCopyCells(CellsToDrawSOA *originalCd);

  /*
   * Generate random values for each array
   */
  static void initializeCells(CellsToDrawSOA *cd);
  /*
   * Iterates the given cells to the next generation.
   *
   * Ruleset (from wikipedia):
   * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life): Any live cell with
   * fewer than two live neighbours dies, as if by underpopulation. Any live
   * cell with two or three live neighbours lives on to the next generation. Any
   * live cell with more than three live neighbours dies, as if by
   * overpopulation. Any dead cell with exactly three live neighbours becomes a
   * live cell, as if by reproduction.
   *
   */
  static void nextGeneration(CellsToDrawSOA *cd, CellsToDrawSOA *previousCd);

private:
  /*
   * Counts the neighbours for the given cell.
   * Every cell interacts with its eight neighbours, which are the cells that
   * are horizontally, vertically, or diagonally adjacent.
   *
   * @return int: the number of neighbours
   */
  static int checkNeighbours(CellsToDrawSOA *previousCd, int i);
} Generator;

} // namespace Gol2d
#endif
