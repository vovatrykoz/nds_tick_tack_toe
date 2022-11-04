using namespace std;

#include <grid.h>
#include <string>

int Grid::getSize() {
  return gridSize;
}

Cell* Grid::getGridArray() {
  return gridArray;
}


Grid::Grid(int size) : gridSize(size) {
  gridArray = (Cell*)calloc(sizeof(Cell), size);
  //gridArray = NULL;
}

Grid::~Grid() {
  free(gridArray);
}