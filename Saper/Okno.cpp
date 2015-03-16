#include "Okno.h"
//#include "Menu.h"
#include <vector>

Window console = Window();

Window gameWindow = Window(console.lines() - 5, console.columns() - 8, 3, 4);

Window shadow = Window(console.lines() - 5, console.columns() - 8, 4, 6);

int ile = 2;
std::string nazwy[] = { "Nowa Gra", "Zamknij" };
int specjalne[] = { 0, 0 };

//Menu& menu = Menu(nazwy, specjalne, ile, gameWindow, gameWindow.lines() - 2, 5, false);

void Okno::Initialize() {
	console << "Saper v0.0.0" << endl;
	console << "__________________________________________________________________________________________________________________________________________________________________________" << endl;

	ColorPair okno1 = ColorPair(COLOR_BLACK, COLOR_WHITE);
	ColorPair cien = ColorPair(COLOR_WHITE, COLOR_BLACK);

	gameWindow.AttrOn(okno1);
	shadow.Background(cien);

	SetBorderColoured(gameWindow);
	//gameWindow << menu;

	gameWindow.AttrOn(okno1);
	gameWindow.Background(okno1);
}

void Okno::SetBorderColoured(Window& window) {
	ColorPair upleft = ColorPair(COLOR_WHITE, COLOR_WHITE);
	ColorPair downright = ColorPair(COLOR_BLACK, COLOR_WHITE);

	window.AttrOn(A_BOLD);

	window.AttrOn(upleft);

	//gameWindow.MoveCursor(0, 0);
	window << WACS_ULCORNER;

	for (register int i = 1; i < window.lines() - 1; ++i) {
		window.MoveCursor(i, 0);
		window << WACS_VLINE;
	}
	for (register int i = 1; i < window.columns() - 1; ++i) {
		window.MoveCursor(0, i);
		window << WACS_HLINE;
		window.MoveCursor(window.lines() - 3, i);
		window << WACS_HLINE;
	}

	window.MoveCursor(window.lines() - 3, 0);
	window << WACS_LTEE;

	window.AttrOff(upleft);
	window.AttrOff(A_BOLD);

	window.AttrOn(downright);

	window.MoveCursor(0, window.columns()-1);
	window << WACS_URCORNER;

	window.MoveCursor(window.lines() - 1, window.columns() - 1);
	window << WACS_LRCORNER;

	window.MoveCursor(window.lines() - 1, 0);
	window << WACS_LLCORNER;

	for (register int i = 1; i < window.lines()-1; ++i) {
		window.MoveCursor(i, window.columns()-1);
		window << WACS_VLINE;
	}
	for (register int i = 1; i < window.columns()-1; ++i) {
		window.MoveCursor(window.lines()-1, i);
		window << WACS_HLINE;
	}

	window.MoveCursor(window.lines() - 3, window.columns() - 1);
	window << WACS_RTEE;
	
	window.AttrOff(downright);
}
