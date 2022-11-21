#include "cell.h"
#include <vector>

class Grid {
    private:
      const int gridSize;
      vector<vector<Cell>> gridArray;

    public:
      const int getSize() const;

      vector<vector<Cell>> getGridArray() const;

      Cell getCell(int posX, int posY) const;

      cellMark checkVictoryCondition() const;

      void makeMove(int posX, int posY, cellMark mark);

      Grid(int size);
};