#include "cell.h"

class Grid {
    private:
      int gridSize;
      Cell grid[0][0];

    public:
      int getSize();

      Grid(int size);
};