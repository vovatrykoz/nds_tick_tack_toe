#include "cell.h"
#include <vector>

class Grid {
    private:
      const int gridSize;
      vector<vector<Cell>> gridArray;

    public:
      const int getSize() const;

      vector<vector<Cell>> getGridArray() const;

      Grid(int size);
};