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

Grid::Grid(int size) : gridSize(size) {}