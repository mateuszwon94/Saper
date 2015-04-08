﻿#include "Wszystko.h"
#include <string>

int main(int argc, char *argv[]) {
	using namespace std;

	initscr();

	Window console = Window(LINES, COLS, 0, 0, stdscr);

	Window gameWindow = Window(console.lines() - 5, console.columns() - 8, 3, 4);

	keypad(console, true);

	Window shadow = Window(console.lines() - 5, console.columns() - 8, 4, 6);

	Okno::Initialize(console, gameWindow, shadow);

	int planszaLines = 40;
	int planszaCols = 70;

	for (int i = 0; i < planszaLines; ++i) {
		for (int j = 0; j < planszaCols; ++j) {
			gameWindow.MoveCursor(i+2, j+2);
			gameWindow << mediumDestinyDots;
		}
	}

	Menu& menu = Menu({ "1. Nowa Gra", "2. Poddaj sie", "3. Wyniki", "4. Zakoncz" }, { 3,3,3,3 }, 4, 80);

	gameWindow << menu;

	char sign;
	do {
		switch (console >> sign) {
			case 'N':
			case 'n':
				menu.SetCurrentEntry(0);
				break;
			case 'P':
			case 'p':
				menu.SetCurrentEntry(1);
				break;
			case 'W':
			case 'w':
				menu.SetCurrentEntry(2);
				break;
			case 'Z':
			case 'z':
				menu.SetCurrentEntry(3);
				break;
			case KEY_UP:
				menu.MoveUp();
				break;
			case KEY_DOWN:
				menu.MoveDown();
				break;
			default:
				menu.SetCurrentEntry();
				break;
		}

		if (menu.CurrentEntry() != -1)
			console.MoveCursor(gameWindow.x() + menu.PosLine()  + menu.CurrentEntry() * 2, gameWindow.y() + menu.PosColumn() + menu[menu.CurrentEntry()].Special());
	} while (menu.CurrentEntry() != 3);

	getch();
	endwin();
	
	return 0;
}