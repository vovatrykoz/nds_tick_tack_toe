#include "cell.h"

class Grid {
    private:
      const int gridSize;
      Cell** gridArray;

    public:
      const int getSize() const;

      Cell** getGridArray() const;

      cellMark checkVictoryCondition() const;

      Grid(int size);

      ~Grid();
};