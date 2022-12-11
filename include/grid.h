#include <cell.h>
#include <gridSupervisor.h>

class Grid {
    private:
      const int gridSize;

      // Use a two-dimensional array to store the grid
    std::array<std::array<CellMark, MAX_GRID_SIZE>, MAX_GRID_SIZE> grid;

    // Use a bitset to keep track of the rows, columns, and diagonals that are still in play
    std::bitset<MAX_GRID_SIZE * 3> inPlay;

    public:
      Grid(int size);

      const int getSize() const;

      Cell** getGridArray() const;

      GridSupervisor getGridSuper() const;

      CellMark checkVictoryCondition() const;

      CellMark checkVictoryRow(int rowPos) const;

      CellMark checkVictoryCol(int colPos) const;

      CellMark checkVictorySouthEastDiag() const;

      CellMark checkVictorySouthWestDiag() const;

      void makeMove(int posX, int posY, CellMark mark);

      ~Grid();
};