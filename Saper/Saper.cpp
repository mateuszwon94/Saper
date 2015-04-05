#include "Wszystko.h"
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[]) {

	initscr();

	Window console = Window(LINES, COLS, 0, 0, stdscr);

	Window gameWindow = Window(console.lines() - 5, console.columns() - 8, 3, 4);

	Window shadow = Window(console.lines() - 5, console.columns() - 8, 4, 6);

	Okno::Initialize(console, gameWindow, shadow);

	int planszaLines = 66;
	int planszaCols = 125;

	for (int i = 0; i < planszaLines; ++i) {
		for (int j = 0; j < planszaCols; ++j) {
			gameWindow.MoveCursor(i+2, j+2);
			gameWindow << mediumDestinyDots;
		}
	}

	getch();

	return 0;
}

/*
<input class="xtext1" id="xcaracter1" type="text" name="xcaracter1" value="└" onclick="this.form.xcaracter1.select()">
*/

