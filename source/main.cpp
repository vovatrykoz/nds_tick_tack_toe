using namespace std;

#include <nds.h>
#include <stdio.h>
#include <grid.h>
#include <string>
#include <iostream>

void drawGrid(Grid grid, PrintConsole *console);
void drawCell(PrintConsole *console, int x, int y);

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

    int size = 5;

    touchPosition touch;

	PrintConsole *console = consoleDemoInit(); 

	Grid grid = Grid(size);

	while(1) 
	{
		int keys;
		
		scanKeys();
		
		keys = keysHeld();

		if(keys & KEY_START) break;
		
		if(keys & KEY_TOUCH)
		{
			touchRead(&touch);

			drawGrid(grid, console);
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

void drawGrid(Grid grid, PrintConsole *console) {
	int size = grid.getSize();

	consoleSelect(console);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			drawCell(console, 5 + 2 * i, 5 + 2 * j);
		}
	}
}

void drawCell(PrintConsole *console, int x, int y) {
	string emptyCell = "+-+"
	                   "| |"
			           "+-+";

	consoleSetWindow(console, x, y, 3, 3);
	cout << emptyCell;	
}