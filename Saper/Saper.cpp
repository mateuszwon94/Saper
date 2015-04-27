#include "Wszystko.h"
#include "Plansza.h"
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[]) {

	initscr();

	Window console = Window(LINES, COLS, 0, 0, stdscr);

	Window gameWindow = Window(console.lines() - 5, console.columns() - 8, 3, 4);

	Window shadow = Window(console.lines() - 5, console.columns() - 8, 4, 6);

	Okno::Initialize(console, gameWindow, shadow);

	int planszaLines = 20;
	int planszaCols = 40;

	Plansza plansza(planszaCols, planszaLines, 20,  &gameWindow);

	getch();

	return 0;
}

/*
<input class="xtext1" id="xcaracter1" type="text" name="xcaracter1" value="└" onclick="this.form.xcaracter1.select()">
*/

