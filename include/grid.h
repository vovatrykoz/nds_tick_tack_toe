#include "cell.h"

class Grid {
    private:
      int gridSize;
      Cell* gridArray;

    public:
      int getSize();

      Cell* getGridArray();

      Grid(int size);

      ~Grid();
};