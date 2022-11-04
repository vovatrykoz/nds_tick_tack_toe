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

void test(Grid grid, PrintConsole *console);
void drawGrid(Cell **grid, int size, PrintConsole *console);
void drawCell(cellMark mark, int x, int y, PrintConsole *console);

int determineXCoords(int offsetX);
int determineYCoords(int offsetY);

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

    int size = 2;

    touchPosition touch;

	PrintConsole *console = consoleDemoInit(); 

	Grid grid(size);

	if(!grid.getGridArray()) {
		consoleSelect(console);
		consoleSetWindow(console, 0, 0, 30, 1);

		cout << "Grid memory allocation failure";
		exit(EXIT_FAILURE);		  
	}

	//debug
	grid.getGridArray()[0][0].setMark(Cross);
	grid.getGridArray()[1][1].setMark(Circle);

	drawGrid(grid.getGridArray(), size, console);

	//test(grid, console);

	while(1) 
	{
		int keys;
		
		scanKeys();
		
		keys = keysHeld();

		if(keys & KEY_START) break;
		
		if(keys & KEY_TOUCH)
		{
			consoleClear();

			drawGrid(grid.getGridArray(), size, console);
			//test(grid, console);

			touchRead(&touch);

			consoleSetWindow(console, 0, 0, 30, 10);

			cout << touch.px;
			cout << "\n";
			cout << touch.py;
			cout << "\n";
			if(touch.px > TOUCH_X_BASE_PX && touch.py > TOUCH_Y_BASE_PX) {
				cout << determineXCoords(touch.px);
				cout << "\n";
				cout << determineYCoords(touch.py);
			}

			grid.getGridArray()[0][0].setMark(Empty);
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

void drawGrid(Cell **grid, int size, PrintConsole *console) {
	//int size = grid.getSize();
	//Cell** gridArr = grid.getGridArray();

	Cell** gridArr = grid;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			drawCell(gridArr[j][i].getMark(), 5 + 2 * j, 5 + 2 * i, console);
		}
	}
}

void drawCell(cellMark mark, int x, int y, PrintConsole *console) {
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
	case Cross:
		cout << crossedCell;
		break;
		
	case Circle:
		cout << circledCell;
		break;
	
	default:
	    cout << emptyCell;
		break;
	}	
}


void test(Grid grid, PrintConsole *console) {
	int size = grid.getSize();
	Cell** gridArr = grid.getGridArray();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			drawCell(gridArr[j][i].getMark(), GRID_OFFSET + 2 * j, GRID_OFFSET + 2 * i, console);
		}
	}
}

int determineXCoords(int offsetX) {
	return (offsetX - TOUCH_X_BASE_PX) / TOUCH_X_PIX_STEP;
}

int determineYCoords(int offsetX) {
	return (offsetX - TOUCH_Y_BASE_PX) / TOUCH_Y_PIX_STEP;
}
