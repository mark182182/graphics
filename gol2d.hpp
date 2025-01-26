#ifndef GOL2D_H
#define GOL2D_H

#include <raylib.h>
#include <unordered_map>

namespace Gol2d {
const int CELL_HEIGHT_SIZE = 10;
const int CELL_WIDTH_SIZE = 10;
const int INITIAL_FREQUENCY = 15;

// Diagonals relative to the current cell: x-1 y+1; x+1 y+1; x-1 y-1; x+1 y-1;
const Vector2 DIAGONALS[4] = {Vector2{-1, 1}, Vector2{1, 1}, Vector2{-1, -1},
                              Vector2{1, -1}};
// Adjecent relative to the current cell: x0 y+1; x-1 y0; x0 y-1; x+1 y0;
const Vector2 ADJECENTS[4] = {Vector2{0, 1}, Vector2{-1, 0}, Vector2{0, -1},
                              Vector2{1, 0}};

typedef struct Cell {
  bool is_alive; // populated or unpopulated
} Cell;

typedef struct CellsToDrawSOA {
  std::unordered_map<std::string, bool>
      *cellAliveByXY; // in order to lookup the neighbours based on pos
                      // x+y (horrible way)
  Cell **cells;
  int *positionsX;
  int *positionsY;
  Color **colors;
  int cellCount;
} CellsToDrawSOA;

typedef struct Generator {
  static void initArraysSizeBasedOnScreenSize(CellsToDrawSOA *cd);
  static void freeArrays(CellsToDrawSOA *cd);

  /*
   * Creates a deep copy of the given CellsToDrawSOA and returns its pointer.
   */
  static CellsToDrawSOA *deepCopy(CellsToDrawSOA *originalCd);

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
  static int checkNeighbours(CellsToDrawSOA *cd, int cellPosX, int cellPosY);
  static void addNeighbourIfPresent(CellsToDrawSOA *cd, int checkPosX,
                                    int checkPosY, int *neigbours);
} Generator;

} // namespace Gol2d
#endif
