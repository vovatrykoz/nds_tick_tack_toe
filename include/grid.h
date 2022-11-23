#include <cell.h>
#include <gridSupervisor.h>

class Grid {
    private:
      const int gridSize;
      Cell** gridArray;
      GridSupervisor supervisor;

    public:
      const int getSize() const;

      Cell** getGridArray() const;

      Grid(int size);

      CellMark checkVictoryCondition() const;

      CellMark checkVictoryRow(int rowPos) const;

      CellMark checkVictoryCol(int colPos) const;

      CellMark checkVictorySouthEastDiag() const;

      CellMark checkVictorySouthWestDiag() const;

      void makeMove(int posX, int posY, CellMark mark) const;

      ~Grid();
};