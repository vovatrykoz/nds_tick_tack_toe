#include <cell.h>
#include <gridSupervisor.h>

class Grid {
    private:
      const int gridSize;

      Cell** gridArray;
      GridSupervisor supervisor;

    public:
      const int getSize() const;

      vector<vector<Cell>> getGridArray() const;

      Cell getCell(int posX, int posY) const;

      cellMark checkVictoryCondition() const;
      
      CellMark checkVictoryCondition() const;

      CellMark checkVictoryRow(int rowPos) const;

      CellMark checkVictoryCol(int colPos) const;

      CellMark checkVictorySouthEastDiag() const;

      CellMark checkVictorySouthWestDiag() const;

      void makeMove(int posX, int posY, CellMark mark) const;

      ~Grid();
};