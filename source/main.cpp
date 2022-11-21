using namespace std;

#include <nds.h>
#include <stdio.h>
#include <grid.h>
#include <string>
#include <ctime>
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
enum Difficulties { Easy, Hard };

static const string emptyCell = "+-+"
	                            "| |"
			                    "+-+";

static const string crossedCell = "+-+"
								  "|x|"
								  "+-+";

static const string circledCell = "+-+"
								  "|o|"
								  "+-+";

void DrawGrid(Cell **grid, const int size, PrintConsole *console);
void DrawCell(CellMark mark, int x, int y, PrintConsole *console);
bool ProcessUserInput(touchPosition touch, Grid* grid, Turn *turn, int maxXStretch, int maxYStretch);
void Renderer(const Grid* grid, PrintConsole *console);
void fastPrint(int posX, int posY, int printNum);
bool RegisterMove(Grid* grid, Turn* turn, int posX, int posY);
void GenerateAiMove(Difficulties diff, Grid* grid, Turn* turn );

int DetermineXCoords(int pixelX);
int DetermineYCoords(int pixelY);

void PrintDebugInfo(PrintConsole *console, touchPosition touch, int maxXStretch, int maxYStretch, Cell** grid, int size);

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
    const unsigned int size = 10;
	int maxXStretch = TOUCH_X_BASE_PX + 16 * size;
	int maxYStretch = TOUCH_Y_BASE_PX + 16 * size;
	Turn turn = Cross;
	static const char *enumCellMarkStr[] = { "Empty", "Crosses", "Circles" };
	GameMode mode = Singleplayer;
	Difficulties diffic = Easy;
	srand((unsigned) time(NULL));

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

	int keys;
	CellMark winner = Empty;

	while(1) 
	{		
		scanKeys();
		
		keys = keysHeld();

		if(keys == KEY_START) break;
		
		if(keys == KEY_TOUCH)
		{
			Renderer(&grid, console);
			touchRead(&touch);

			//PrintDebugInfo(console, touch, maxXStretch, maxYStretch, grid.getGridArray(), grid.getSize());

		    if(winner == Empty) {
				if(ProcessUserInput(touch, &grid, &turn, maxXStretch, maxYStretch) && winner == Empty) {
					winner = grid.checkVictoryCondition();
				}
			} else {
				consoleSetWindow(console, 4, 2, 20, 3);
				cout << enumCellMarkStr[winner] << " win!";
			}
		}
		swiWaitForVBlank();
	}
	return 0;
}

void GenerateAiMove(Difficulties diff, Grid* grid, Turn* turn) {
	int size = grid->getSize();
	while(!RegisterMove(grid, turn, rand() % size, rand() % size));
}

bool ProcessUserInput(touchPosition touch, Grid* grid, Turn* turn, int maxXStretch, int maxYStretch) {
	//if within the grid
	if((touch.px > TOUCH_X_BASE_PX && touch.px < maxXStretch) && (touch.py > TOUCH_Y_BASE_PX && touch.py < maxYStretch)) {
		return RegisterMove(grid, turn, DetermineXCoords(touch.px), DetermineYCoords(touch.py));
	}

	return false;
}

bool RegisterMove(Grid* grid, Turn* turn, int posX, int posY) {
	CellMark currMark = grid->getGridArray()[posX][posY].getMark();

	if(currMark == Empty && *turn == Cross) {
		grid->makeMove(posX, posY, X);
		*turn = Circle;
		return true;
	} else if (currMark == Empty && *turn == Circle) {
		grid->makeMove(posX, posY, O);
		*turn = Cross;
		return true;
	}

	return false;
}

void Renderer(const Grid *grid, PrintConsole *console) {
	consoleClear();
	DrawGrid(grid->getGridArray(), grid->getSize(), console);
}

void DrawGrid(Cell **grid, int size, PrintConsole *console) {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			DrawCell(grid[j][i].getMark(), 5 + 2 * j, 5 + 2 * i, console);
}

void DrawCell(CellMark mark, int x, int y, PrintConsole *console) {
	consoleSelect(console);
	consoleSetWindow(console, x, y, 3, 3);

	switch (mark) {
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

	consoleSetWindow(console, 25, 0, 10, 10);

	for(int i = 0; i < size; i++)
	    for(int j = 0; j < size; j++) {
			cout << j << i << "->" << grid[j][i].getMark() << "\n";
		}
}

