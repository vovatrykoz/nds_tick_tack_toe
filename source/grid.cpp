using namespace std;

#include <grid.h>
#include <string>
#include <iostream> //DEBUG ONLY REMOVE LATER

Grid::Grid(int size) : gridSize(size) {
  gridArray = (Cell**)calloc(sizeof(Cell*), gridSize);

  for(int i = 0; i < gridSize; i++) {
    gridArray[i] = (Cell*)calloc(sizeof(Cell), gridSize);
  }
}

const int Grid::getSize() const {
  return gridSize;
}

Cell** Grid::getGridArray() const {
  return gridArray;
}

GridSupervisor Grid::getGridSuper() const {
  return supervisor;
}

CellMark Grid::checkVictoryCondition() const {
	CellMark res = Empty;
	int doubleSize = gridSize * 2;

	for(unsigned int i = 0; i < supervisor.getSupervSize(); i++) {
		if(supervisor.getSupervArr()[i].compStat == Winnable) {

			int compId = supervisor.getSupervArr()[i].compId;

			if(compId >= 0 && compId < gridSize) {
				res = checkVictoryRow(compId);
				if(res != Empty)
					return res;
			} else if(compId >= gridSize && compId < doubleSize) {
				res = checkVictoryCol(compId - gridSize);
				if(res != Empty)
					return res;
			} else if(compId == doubleSize) {
				res = checkVictorySouthEastDiag();
				if(res != Empty)
					return res;
			} else if(compId == doubleSize + 1) {
				res = checkVictorySouthWestDiag();
				if(res != Empty)
					return res;
			}
		}
	}

	return res;
}

CellMark Grid::checkVictoryRow(int rowPos) const {
	int counter = 0;

	if(gridArray[0][rowPos].getMark() == Empty) 
	    return Empty;

	for(int i = 0; i < gridSize - 1; i++) {
		if(gridArray[i + 1][rowPos].getMark() == Empty) break;

		if(gridArray[i][rowPos].getMark() == gridArray[i + 1][rowPos].getMark())
			counter++;
		else 
			break;
	}

	if(counter == gridSize - 1) {
		return gridArray[counter][rowPos].getMark();
	}

	return Empty;
}

CellMark Grid::checkVictoryCol(int colPos) const {
	int counter = 0;

	if(gridArray[colPos][0].getMark() == Empty) 
	    return Empty;

	for(int i = 0; i < gridSize - 1; i++) {
		if(gridArray[colPos][i + 1].getMark() == Empty) break;

		if(gridArray[colPos][i].getMark() == gridArray[colPos][i + 1].getMark())
			counter++;
		else
			break;
	}

	if(counter == gridSize - 1) {
		return gridArray[colPos][counter].getMark();
	}

	return Empty;
}

CellMark Grid::checkVictorySouthEastDiag() const {
	int counter = 0;

	if(gridArray[0][0].getMark() == Empty)
	    return Empty;

	//check diagonally (left to right)
	for(int i = 0, j = 0; i < gridSize - 1; i++) {
		if(gridArray[i + 1][j + 1].getMark() == Empty)
			break;

		if(gridArray[i][j].getMark() == gridArray[i + 1][j + 1].getMark())
			counter++;
		else
			break;

		j++;
	}

	if(counter == gridSize - 1) {
		return gridArray[0][0].getMark();
	}

	return Empty;
}

CellMark Grid::checkVictorySouthWestDiag() const {
	int counter = 0;

	if(gridArray[gridSize - 1][0].getMark() == Empty)
	    return Empty;

	//check diagonally (right to left)
	for(int i = gridSize - 1, j = 0; i >= 0; i--) {
		if(gridArray[i - 1][j + 1].getMark() == Empty)
			break;

		if(gridArray[i][j].getMark() == gridArray[i - 1][j + 1].getMark())
			counter++;
		else
			break;

		j++;
	}

	if(counter == gridSize - 1) {
		return gridArray[0][counter].getMark();
	}

	return Empty;
}

void Grid::makeMove(int posX, int posY, CellMark mark) {
	gridArray[posX][posY].setMark(mark);
	supervisor.processSubComponent(posX, posY, gridSize, mark);
}

Grid::~Grid() {
  for(int i = 0; i < gridSize; i++) {
    free(gridArray[i]);
  }
  
  free(gridArray);
}

