using namespace std;

#include <nds.h>
#include <stdio.h>
#include <grid.h>
#include <string>
#include <iostream>

#define stringify( name ) #name
#define GRID_OFFSET 5
//position of the first pixel of the first square
#define TOUCH_X_BASE_PX 45
#define TOUCH_Y_BASE_PX 45
#define TOUCH_X_PIX_STEP 16
#define TOUCH_Y_PIX_STEP 16

enum Turn { Cross, Circle };
enum GameMode { Singleplayer, Multiplayer };

static const string emptyCell = "+-+"
	                            "| |"
			                    "+-+";

static const string crossedCell = "+-+"
								  "|x|"
								  "+-+";

static const string circledCell = "+-+"
								  "|o|"
								  "+-+";

void DrawGrid(vector<vector<Cell>> grid, const int size, PrintConsole *console);
void DrawCell(cellMark mark, int x, int y, PrintConsole *console);
cellMark CheckVictoryCondition(const Grid *grid);
void ProcessUserInput(touchPosition touch, Grid* grid, Turn *turn, int maxXStretch, int maxYStretch);
void Renderer(const Grid* grid, PrintConsole *console);
void fastPrint(int posX, int posY, int printNum);
void RegisterMove(Grid* grid, Turn* turn, int posX, int posY);

int DetermineXCoords(int pixelX);
int DetermineYCoords(int pixelY);

void PrintDebugInfo(PrintConsole *console, touchPosition touch, int maxXStretch, int maxYStretch, vector<vector<Cell>> grid, int size,  const Grid* gr);

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
    const unsigned int size = 3;
	int maxXStretch = TOUCH_X_BASE_PX + 16 * size;
	int maxYStretch = TOUCH_Y_BASE_PX + 16 * size;
	Turn turn = Cross;
	static const char *enumCellMarkStr[] = { "Empty", "Crosses", "Circles" };
	//GameMode mode;

    touchPosition touch;

	PrintConsole *console = consoleDemoInit(); 

	Grid grid(size);

	Renderer(&grid, console);

	cout << &(grid.getGridArray()[2][1]);

	int keys;
	cellMark winner = Empty;

	while(1) 
	{		
		scanKeys();
		
		keys = keysHeld();

		if(keys == KEY_START) break;
		
		if(keys == KEY_TOUCH)
		{
			Renderer(&grid, console);

			touchRead(&touch);

			PrintDebugInfo(console, touch, maxXStretch, maxYStretch, grid.getGridArray(), grid.getSize(), &grid);

		    if(winner == Empty) {
				winner = grid.checkVictoryCondition();
				ProcessUserInput(touch, &grid, &turn, maxXStretch, maxYStretch);
			} else {
				consoleSetWindow(console, 4, 2, 20, 3);
				cout << enumCellMarkStr[winner] << " win!";
			}
		}
		swiWaitForVBlank();
	}
	return 0;
}

void ProcessUserInput(touchPosition touch, Grid* grid, Turn* turn, int maxXStretch, int maxYStretch) {
	//if within the grid
	cout << &(grid->getGridArray()[2][1]);
	if((touch.px > TOUCH_X_BASE_PX && touch.px < maxXStretch) && (touch.py > TOUCH_Y_BASE_PX && touch.py < maxYStretch))
		RegisterMove(grid, turn, DetermineXCoords(touch.px), DetermineYCoords(touch.py));
}

void RegisterMove(Grid* grid, Turn* turn, int posX, int posY) {
	//Cell* currCell = &(grid->getGridArray()[posX][posY]);

	if(grid->getGridArray()[posX][posY].getMark() == Empty && *turn == Cross) {
		grid->getGridArray()[posX][posY].setMark(X);
		*turn = Circle;
	} else if (grid->getGridArray()[posX][posY].getMark() == Empty && *turn == Circle) {
		grid->getGridArray()[posX][posY].setMark(O);
		*turn = Cross;
	}
}

void Renderer(const Grid *grid, PrintConsole *console) {
	consoleClear();
	DrawGrid(grid->getGridArray(), grid->getSize(), console);
}

void DrawGrid(vector<vector<Cell>> grid, int size, PrintConsole *console) {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			DrawCell(grid[j][i].getMark(), 5 + 2 * j, 5 + 2 * i, console);
}

void DrawCell(cellMark mark, int x, int y, PrintConsole *console) {
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

void PrintDebugInfo(PrintConsole *console, touchPosition touch, int maxXStretch, int maxYStretch, vector<vector<Cell>> grid, int size, const Grid* gr) {
	consoleSetWindow(console, 20, 20, 10, 10);

	cout << &(gr->getGridArray()[0][0]);

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

	consoleSetWindow(console, 25, 0, 10, 10);

	for(int i = 0; i < size; i++)
	    for(int j = 0; j < size; j++) {
			cout << j << i << "->" << grid[j][i].getMark() << "\n";
		}
}

