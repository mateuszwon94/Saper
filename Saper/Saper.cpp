#include "Wszystko.h"

int main(int argc, char *argv[]) {

	initscr();
	//resize_term(100, 100);
	Window console = Window(LINES, COLS, 0, 0, stdscr);

	Window gameWindow = Window(console.lines() - 5, console.columns() - 8, 3, 4);

	Window shadow = Window(console.lines() - 5, console.columns() - 8, 4, 6);

	Okno::Initialize(console, gameWindow, shadow);

	gameWindow.MoveCursor(5, 20);
	gameWindow << "tekst";
	//mvprintw(LINES - 2, 0, "This screen has %d rows and %d columns\n", LINES, COLS);
	getch();

	return 0;
}

