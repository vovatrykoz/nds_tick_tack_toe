using namespace std;

#include <nds.h>
#include <stdio.h>
#include <grid.h>
#include <string>
#include <iostream>

#define GRID_OFFSET 5
//position of the first pixel of the first square
#define TOUCH_X_BASE_PX 45
#define TOUCH_Y_BASE_PX 45
#define TOUCH_X_PIX_STEP 16
#define TOUCH_Y_PIX_STEP 16

enum Turn { Cross, Circle };

void DrawGrid(Cell **grid, const int size, PrintConsole *console);
void DrawCell(cellMark mark, int x, int y, PrintConsole *console);
cellMark CheckVictoryCondition(Cell** grid, int size);
void ProcessUserInput(touchPosition touch, Grid* grid, Turn *turn, int maxXStretch, int maxYStretch);
void Renderer(const Grid* grid, PrintConsole *console);

int DetermineXCoords(int pixelX);
int DetermineYCoords(int pixelY);

void PrintDebugInfo(PrintConsole *console, touchPosition touch, int maxXStretch, int maxYStretch, Cell** grid, int size);

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

    const unsigned int size = 3;
	int maxXStretch = TOUCH_X_BASE_PX + 16 * size;
	int maxYStretch = TOUCH_Y_BASE_PX + 16 * size;
	Turn turn = Cross;

    touchPosition touch;

	PrintConsole *console = consoleDemoInit(); 

	Grid grid(size);

	if(!grid.getGridArray()) {
		consoleSelect(console);
		consoleSetWindow(console, 0, 0, 30, 1);

		cout << "Grid memory allocation failure";
		exit(EXIT_FAILURE);		  
	}

	DrawGrid(grid.getGridArray(), size, console);

	while(1) 
	{
		int keys;
		cellMark winner;
		
		scanKeys();
		
		keys = keysHeld();

		if(keys == KEY_START) break;
		
		if(keys == KEY_TOUCH)
		{
			Renderer(&grid, console);

			winner = CheckVictoryCondition(grid.getGridArray(), grid.getSize());

			touchRead(&touch);

			PrintDebugInfo(console, touch, maxXStretch, maxYStretch, grid.getGridArray(), grid.getSize());

		    if(winner == Empty) {
				ProcessUserInput(touch, &grid, &turn, maxXStretch, maxYStretch);
			} else {
				consoleSetWindow(console, 2, 2, 20, 3);
				cout << winner << " is the winner!";
			}
		}

		swiWaitForVBlank();
	}

/*
	touchPosition touch;

	PrintConsole *console = consoleDemoInit();  
	PrintConsole right = *console;	
	
	consoleSetWindow(console, 15,1,12,16);
	consoleSetWindow(&right, 1,1,12,16);

	consoleSelect(console);
	iprintf(border);
	consoleSelect(&right);
	iprintf(border);

	consoleSetWindow(console, 2,2,10,14);
	consoleSetWindow(&right,16,2,10,14);
	
	while(1) 
	{
		int keys;
		
		scanKeys();
		
		keys = keysHeld();

		if(keys & KEY_START) break;
		
		if(keys & KEY_TOUCH)
		{
			touchRead(&touch);
			
			if(touch.px < 128)
				consoleSelect(console);
			else
				consoleSelect(&right);
				
			iprintf("\nT: %i", touch.px);
		}

		swiWaitForVBlank();
	}
*/
	return 0;
}

void ProcessUserInput(touchPosition touch, Grid* grid, Turn* turn, int maxXStretch, int maxYStretch) {
	//if within the grid
	if((touch.px > TOUCH_X_BASE_PX && touch.px < maxXStretch) && (touch.py > TOUCH_Y_BASE_PX && touch.py < maxYStretch)) {
		//get cell coordinates
		Cell* currCell = &(grid->getGridArray()[DetermineXCoords(touch.px)][DetermineYCoords(touch.py)]);

		if(currCell->getMark() == Empty && *turn == Cross) {
			currCell->setMark(X);
			*turn = Circle;
		} else if (currCell->getMark() == Empty && *turn == Circle) {
			currCell->setMark(O);
			*turn = Cross;
		}
	}
}

void Renderer(const Grid *grid, PrintConsole *console) {
	consoleClear();
	DrawGrid(grid->getGridArray(), grid->getSize(), console);
}

cellMark CheckVictoryCondition(Cell** grid, int size) {
	int counter;

	//check horizontally
	for(int i = 0; i < size; i++) {
		counter = 0;
		for(int j = 0; j < size - 1; j++) {
			if(grid[j][i].getMark() == Empty || grid[j + 1][i].getMark() == Empty) break;

			if(grid[j][i].getMark() == grid[j + 1][i].getMark()) {
				counter++;

			    if(counter == size - 1) {
				    return grid[j][i].getMark();
				}
			}
		}
	}

	//check vertically
	for(int i = 0; i < size; i++) {
		counter = 0;
		for(int j = 0; j < size - 1; j++) {
			if(grid[i][j].getMark() == Empty || grid[i][j + 1].getMark() == Empty) break;

			if(grid[i][j].getMark() == grid[i][j + 1].getMark()) {
				counter++;

			    if(counter == size - 1) {
				    return grid[j][i].getMark();
				}
			}
		}
	}

	//reset the counter
	counter = 0;

	//check diagonally (left to right)
	for(int j = 0, i = 0; j < size - 1; j++) {
		if(grid[j][i].getMark() == Empty || grid[j + 1][i + 1].getMark() == Empty) {
			counter = 0;
			break;
		} 

		if(grid[j][i].getMark() == grid[j + 1][i + 1].getMark()) {
			counter++;

			if(counter == size - 1) {
				return grid[j][i].getMark();
			}
		}
		i++;
	}

	//reset the counter
	counter = 0;

	//check diagonally (right to left)
	for(int j = size - 1, i = 0; j >= 0; j--) {
		if(grid[j][i].getMark() == Empty || grid[j - 1][i + 1].getMark() == Empty) {
			counter = 0;
			break;
		} 

		if(grid[j][i].getMark() == grid[j - 1][i + 1].getMark()) {
			counter++;

			if(counter == size - 1) {
				return grid[j][i].getMark();
			}
		}
		i++;
	}

	return Empty;
}

void DrawGrid(Cell **grid, int size, PrintConsole *console) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			DrawCell(grid[j][i].getMark(), 5 + 2 * j, 5 + 2 * i, console);
		}
	}
}

void DrawCell(cellMark mark, int x, int y, PrintConsole *console) {
	string emptyCell = "+-+"
	                   "| |"
			           "+-+";

	string crossedCell = "+-+"
	                     "|x|"
			             "+-+";

	string circledCell = "+-+"
	                     "|o|"
			             "+-+";

	consoleSelect(console);
	consoleSetWindow(console, x, y, 3, 3);

	switch (mark)
	{
	case X:
		cout << crossedCell;
		break;
		
	case O:
		cout << circledCell;
		break;
	
	default:
	    cout << emptyCell;
		break;
	}	
}

int DetermineXCoords(int pixelX) {
	return (pixelX - TOUCH_X_BASE_PX) / TOUCH_X_PIX_STEP;
}

int DetermineYCoords(int pixelY) {
	return (pixelY - TOUCH_Y_BASE_PX) / TOUCH_Y_PIX_STEP;
}

void PrintDebugInfo(PrintConsole *console, touchPosition touch, int maxXStretch, int maxYStretch, Cell** grid, int size) {
	consoleSetWindow(console, 20, 20, 10, 10);

	cout << grid;

	consoleSetWindow(console, 0, 0, 30, 10);

	cout << touch.px;
	cout << "\n";
	cout << touch.py;
	cout << "\n";

	if((touch.px > TOUCH_X_BASE_PX && touch.px < maxXStretch) && (touch.py > TOUCH_Y_BASE_PX && touch.py < maxYStretch)) {
		cout << DetermineXCoords(touch.px);
		cout << "\n";
		cout << DetermineYCoords(touch.py);
	}

	consoleSetWindow(console, 20, 0, 10, 10);

	for(int i = 0; i < size; i++)
	    for(int j = 0; j < size; j++) {
			cout << j << i << "->" << grid[j][i].getMark() << "\n";
		}
}