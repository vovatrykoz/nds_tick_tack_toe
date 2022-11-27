using namespace std;

#include <grid.h>
#include <string>
#include <iostream> //DEBUG ONLY REMOVE LATER

const int Grid::getSize() const {
  return gridSize;
}

vector<vector<Cell>> Grid::getGridArray() const {
  return gridArray;
}

cellMark Grid::checkVictoryCondition() const {
  int counter;

	//check horizontally
	for(int i = 0; i < gridSize; i++) {
		counter = 0;
		for(int j = 0; j < gridSize - 1; j++) {
			if(gridArray[j][i].getMark() == Empty || gridArray[j + 1][i].getMark() == Empty) break;

			if(gridArray[j][i].getMark() == gridArray[j + 1][i].getMark()) {
				counter++;

			    if(counter == gridSize - 1) {
				    return gridArray[j][i].getMark();
				}
			}
		}
	}

	//check vertically
	for(int i = 0; i < gridSize; i++) {
		counter = 0;
		for(int j = 0; j < gridSize - 1; j++) {
			if(gridArray[i][j].getMark() == Empty || gridArray[i][j + 1].getMark() == Empty) break;
			//fastPrint(0 + counter, 5, counter);
			if(gridArray[i][j].getMark() == gridArray[i][j + 1].getMark()) {
				counter++;

			    if(counter == gridSize - 1) {
				    return gridArray[i][j].getMark();
				}
			}
		}
	}

	//reset the counter
	counter = 0;

	//check diagonally (left to right)
	for(int j = 0, i = 0; j < gridSize - 1; j++) {
		if(gridArray[j][i].getMark() == Empty || gridArray[j + 1][i + 1].getMark() == Empty) {
			counter = 0;
			break;
		}

		if(gridArray[j][i].getMark() == gridArray[j + 1][i + 1].getMark()) {
			counter++;

			if(counter == gridSize - 1) {
				return gridArray[j][i].getMark();
			}
		}
		i++;
	}

	//reset the counter
	counter = 0;

	//check diagonally (right to left)
	for(int j = gridSize - 1, i = 0; j >= 0; j--) {
		if(gridArray[j][i].getMark() == Empty || gridArray[j - 1][i + 1].getMark() == Empty) {
			counter = 0;
			break;
		} 

		if(gridArray[j][i].getMark() == gridArray[j - 1][i + 1].getMark()) {
			counter++;

			if(counter == gridSize - 1) {
				return gridArray[j][i].getMark();
			}
		}
		i++;
	}

	return Empty;
}

Cell Grid::getCell(int posX, int posY) const {
	return gridArray[posX][posY];
}

void Grid::makeMove(int posX, int posY, cellMark mark) {
  cout << posX << ' ' << posY << ' ' << mark;
  if(posX < gridSize && posY < gridSize && gridArray[posX][posY].getMark() == Empty)
      gridArray[posX][posY].setMark(mark);
}

CellMark Grid::checkVictoryCondition() const {
	CellMark res;
	//check horizontally
	for(int i = 0; i < gridSize; i++) {
		res = checkVictoryRow(i);
		if(res != Empty)
		    return res;
	}

	//check vertically
	for(int i = 0; i < gridSize; i++) {
		res = checkVictoryCol(i);
		if(res != Empty)
		    return res;
	}

	res = checkVictorySouthEastDiag();
	if(res != Empty)
		return res;

	res = checkVictorySouthWestDiag();

	return res;
}

CellMark Grid::checkVictoryRow(int rowPos) const {
	int counter = 0;

	for(int i = 0; i < gridSize - 1; i++) {
		if(gridArray[i][rowPos].getMark() == Empty || gridArray[i + 1][rowPos].getMark() == Empty) break;

		if(gridArray[i][rowPos].getMark() == gridArray[i + 1][rowPos].getMark()) {
			counter++;

			if(counter == gridSize - 1) {
				return gridArray[i][rowPos].getMark();
			}
		}
	}

	return Empty;
}

CellMark Grid::checkVictoryCol(int colPos) const {
	int counter = 0;

	for(int i = 0; i < gridSize - 1; i++) {
		if(gridArray[colPos][i].getMark() == Empty || gridArray[colPos][i + 1].getMark() == Empty) break;

		if(gridArray[colPos][i].getMark() == gridArray[colPos][i + 1].getMark()) {
			counter++;

			if(counter == gridSize - 1) {
				return gridArray[colPos][i].getMark();
			}
		}
	}

	return Empty;
}

CellMark Grid::checkVictorySouthEastDiag() const {
	int counter = 0;

	//check diagonally (left to right)
	for(int i = 0, j = 0; i < gridSize - 1; i++) {
		if(gridArray[i][j].getMark() == Empty || gridArray[i + 1][j + 1].getMark() == Empty)
			break;

		if(gridArray[i][j].getMark() == gridArray[i + 1][j + 1].getMark()) {
			counter++;

			if(counter == gridSize - 1) {
				return gridArray[i][j].getMark();
			}
		}
		j++;
	}

	return Empty;
}

CellMark Grid::checkVictorySouthWestDiag() const {
	int counter = 0;

	//check diagonally (right to left)
	for(int i = gridSize - 1, j = 0; i >= 0; i--) {
		if(gridArray[i][j].getMark() == Empty || gridArray[i - 1][j + 1].getMark() == Empty)
			break;

		if(gridArray[i][j].getMark() == gridArray[i - 1][j + 1].getMark()) {
			counter++;

			if(counter == gridSize - 1) {
				return gridArray[i][j].getMark();
			}
		}
		j++;
	}

	return Empty;
}

void Grid::makeMove(int posX, int posY, CellMark mark) const {
	gridArray[posX][posY].setMark(mark);
}

Grid::~Grid() {
  for(int i = 0; i < gridSize; i++) {
    free(gridArray[i]);
  }
  
  free(gridArray);
}

