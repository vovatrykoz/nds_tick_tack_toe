using namespace std;

#include <grid.h>
#include <string>

int Grid::getSize() {
  return gridSize;
}

Grid::Grid(int size) {
  gridSize = size;
}