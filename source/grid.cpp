using namespace std;

#include <grid.h>
#include <string>

const int Grid::getSize() const {
  return gridSize;
}

Cell** Grid::getGridArray() const {
  return gridArray;
}


Grid::Grid(int size) : gridSize(size) {
  gridArray = (Cell**)calloc(sizeof(Cell*), gridSize);

  for(int i = 0; i < gridSize; i++) {
    gridArray[i] = (Cell*)calloc(sizeof(Cell), gridSize);
  }
}

Grid::~Grid() {
  for(int i = 0; i < gridSize; i++) {
    free(gridArray[i]);
  }
  free(gridArray);
}