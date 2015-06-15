#pragma execution_character_set("utf-8")
#include "Wszystko.h"


int main(int argc, char *argv[]) {
	using namespace std;

	Okno::Initialize();
	Menu& menu = Menu(
	{ //Vector nazw
		"Latwy",
		"Normalny",
		"Trudny",
		"Wlasny",
		"Graj",
		"Kontynuuj",
		"Wyniki",
		"Pomoc",
		"Zamknij"
	},
	{ //Vector funkcji
		[]() { Plansza::setCLB({ Menu::getColumns(), Menu::getLines(), Menu::getBombs() }); Menu::current().SetCurrentEntry(4); },
		[]() { Plansza::setCLB({ Menu::getColumns(), Menu::getLines(), Menu::getBombs() }); Menu::current().SetCurrentEntry(4); },
		[]() { Plansza::setCLB({ Menu::getColumns(), Menu::getLines(), Menu::getBombs() }); Menu::current().SetCurrentEntry(4); },
		[]() { Plansza::setCLB({ Menu::getColumns(), Menu::getLines(), Menu::getBombs() }); Menu::current().SetCurrentEntry(4); },
		[]() { Plansza::setCurrent(new Plansza()); Plansza::getCurrent().run(); },
		[]() { Plansza::getCurrent().run(); },
		[]() { Results::getInstance()->view(); },
		[]() { Help::View(); },
		[]() { Timer::end(); std::exit(0); }
	},
	{ 0, 0, 0, 0, 0, 0, 1, 0, 0 }, //wektor specjalnych
	5, 80); //pozycja
	//Plansza::setCLB({ 10,10,10 });
	gameWindow << menu;

	menu.MoveCursor(console, gameWindow);
	menu.CallCurrentFunction(console,gameWindow);
	menu.RefreshCLB(gameWindow);

	int sign;

	while (true) {
		console >> sign;
		menu.Move(sign, console, gameWindow);
	}

	Timer::end();

	return 0;
}
