using namespace std;

#include <nds.h>
#include <stdio.h>
#include <grid.h>
#include <string>
#include <iostream>

void drawGrid(Cell** grid, int size, PrintConsole *console);
void drawCell(cellMark mark, int x, int y, PrintConsole *console);

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

	grid.getGridArray()[0][0].setMark(Cross);

	while(1) 
	{
		consoleSelect(console);
		consoleSetWindow(console, 0, 0, 30, 1);

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << grid.getGridArray()[j][i].getMark();
			}			
		}

		drawGrid(grid.getGridArray(), size, console);

		int keys;
		
		scanKeys();
		
		keys = keysHeld();

		if(keys & KEY_START) break;
		
		if(keys & KEY_TOUCH)
		{
			touchRead(&touch);

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

void drawGrid(Cell** grid, int size, PrintConsole *console) {
	//int size = grid.getSize();
	//Cell** gridArr = grid.getGridArray();

	Cell** gridArr = grid;

	//cout << gridArr[0][0].getMark();

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

	consoleSelect(console);
	consoleSetWindow(console, x, y, 3, 3);

	if(mark == 0) {
		cout << emptyCell;	
	} else if (mark == 1) {
		cout << crossedCell;
	}
	
}