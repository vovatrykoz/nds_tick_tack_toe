using namespace std;

#include <grid.h>
#include <string>

const int Grid::getSize() const {
  return gridSize;
}

vector<vector<Cell>> Grid::getGridArray() const {
  return gridArray;
}


Grid::Grid(int size) : gridSize(size) {}