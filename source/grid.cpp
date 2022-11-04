using namespace std;

#include <grid.h>
#include <string>

int Grid::getSize() {
  return gridSize;
}

Cell** Grid::getGridArray() {
  return gridArray;
}


Grid::Grid(int size) : gridSize(size) {
  gridArray = (Cell**)calloc(sizeof(Cell*), gridSize);

  for(int i = 0; i < gridSize; i++) {
    gridArray[i] = (Cell*)calloc(sizeof(Cell), gridSize);
  }
}

Grid::~Grid() {
  free(gridArray);
}