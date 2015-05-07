#include "Wszystko.h"
#include "Plansza.h"
#include "Functions.h"
#pragma execution_character_set("utf-8")
#include <string>

int main(int argc, char *argv[]) {
	using namespace std;

	initscr();
	raw();

	Window& console = Window(LINES, COLS, 0, 0, stdscr);

	Window& gameWindow = Window(console.lines() - 5, console.columns() - 8, 3, 4);

	Window::gw = &gameWindow;

	Window shadow = Window(console.lines() - 5, console.columns() - 8, 4, 6);

	Okno::Initialize(console, gameWindow, shadow);

	Menu& menu = Menu({ "Latwy", "Normalny", "Trudny", "Wlasny", "Graj", "Kontynuuj", "Wyniki", "Zamknij" }, {SetMode, SetMode, SetMode, SetMode, Start, Continue, Results, Quit }, { 0, 0, 0, 0, 0, 0, 1, 0 }, 4, 80);

	gameWindow << menu;

	menu.MoveCursor(console, gameWindow);
	menu.CallCurrentFunction(gameWindow);
	menu.RefreshCLB(gameWindow);

	int sign;
	
	while (true) {
		console >> sign;
		menu.Move(sign, console, gameWindow);
	}
	
	return 0;
}
