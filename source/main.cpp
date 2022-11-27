using namespace std;

#include <string>
#include <ctime>
#include <iostream>
#include <nds.h>
#include <grid.h>
#include <supervElement.h>
#include <vector>

#define stringify( name ) #name
#define GRID_OFFSET 5
//position of the first pixel of the first square
#define TOUCH_BASE_PX 45
//define one step in terms of pixels
#define TOUCH_PIX_STEP 16

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
bool ProcessUserInput(touchPosition touch, Grid* grid, Turn *turn, int maxXStretch, int maxYStretch, vector<supervElement> *gridSuperv);
void Renderer(const Grid* grid, PrintConsole *console);
void fastPrint(int posX, int posY, int printNum);
bool RegisterMove(Grid* grid, Turn* turn, unsigned int posX, unsigned int posY);
void GenerateAiMove(Difficulties diff, Grid* grid, Turn* turn );

int DetermineLineCoord(int pixel);


void PrintDebugInfo(PrintConsole *console, touchPosition touch, int maxXStretch, int maxYStretch, Cell** grid, int size, GridSupervisor super);

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
    const int size = 3;
	int maxXStretch, maxYStretch;
	maxXStretch = maxYStretch = TOUCH_BASE_PX + 16 * size;
	Turn turn = Cross;
	static const char *enumCellMarkStr[] = { "Empty", "Crosses", "Circles" };
	//GameMode mode = Singleplayer;
	//Difficulties diffic = Easy;
	vector<supervElement> gridSuperv;
	//srand((unsigned) time(NULL));

    touchPosition touch;

	PrintConsole *console = consoleDemoInit(); 

	Grid grid(size);

	Renderer(&grid, console);

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

			PrintDebugInfo(console, touch, maxXStretch, maxYStretch, grid.getGridArray(), grid.getSize(), grid.getGridSuper());

		    if(winner == Empty) {
				if(ProcessUserInput(touch, &grid, &turn, maxXStretch, maxYStretch, &gridSuperv)) {
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

bool ProcessUserInput(touchPosition touch, Grid* grid, Turn* turn, int maxXStretch, int maxYStretch, vector<supervElement> *gridSuperv) {
	//if within the grid
	if((touch.px > TOUCH_BASE_PX && touch.px < maxXStretch) && (touch.py > TOUCH_BASE_PX && touch.py < maxYStretch)) {
		unsigned int posX = DetermineLineCoord(touch.px);
		unsigned int posY = DetermineLineCoord(touch.py);			
		return RegisterMove(grid, turn, posX, posY);	
	}

	return false;
}

bool RegisterMove(Grid* grid, Turn* turn, unsigned int posX, unsigned int posY) {
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

int DetermineLineCoord(int pixel) {
	return (pixel - TOUCH_BASE_PX) / TOUCH_PIX_STEP;
}

void PrintDebugInfo(PrintConsole *console, touchPosition touch, int maxXStretch, int maxYStretch, Cell** grid, int size, GridSupervisor super) {
	consoleSetWindow(console, 20, 20, 10, 10);

	cout << grid;

	consoleSetWindow(console, 0, 0, 30, 10);

	cout << touch.px;
	cout << "\n";
	cout << touch.py;
	cout << "\n";

	if((touch.px > TOUCH_BASE_PX && touch.px < maxXStretch) && (touch.py > TOUCH_BASE_PX && touch.py < maxYStretch)) {
		cout << DetermineLineCoord(touch.px);
		cout << "\n";
		cout << DetermineLineCoord(touch.py);
	}

	consoleSetWindow(console, 25, 0, 30, 30);

	//for(unsigned int i = 0; i < super.supervArr.size(); i++)
		//cout << super.supervArr[i].compId;
/*
	for(int i = 0; i < size; i++)
	    for(int j = 0; j < size; j++) {
			cout << j << i << "->" << grid[j][i].getMark() << "\n";
		}*/

	
	//cout << gridSuperv[2].compId;
}