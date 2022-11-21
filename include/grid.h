#include "cell.h"

class Grid {
    private:
      const int gridSize;
      Cell** gridArray;

    public:
      const int getSize() const;

      Cell** getGridArray() const;

      CellMark checkVictoryCondition() const;

      void makeMove(int posX, int posY, CellMark mark) const;

      Grid(int size);

      ~Grid();
};