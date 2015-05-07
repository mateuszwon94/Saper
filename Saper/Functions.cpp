#include "Functions.h"
#include <cstdlib>
#include "Menu.h"
#include "Plansza.h"
#include "Window.h"

void SetMode() {
	Plansza::setColumns(Menu::getColumns());
	Plansza::setLines(Menu::getLines());
	Plansza::setBombs(Menu::getBombs());
}

void Start() { 
	Plansza::setCurrent(new Plansza(Plansza::getColumns(), Plansza::getLines(), Plansza::getBombs(),Window::gw));
	Plansza::getCurrent().run(); 
}

void Continue() { Plansza::getCurrent().run(); }

void Results() { }

void Quit() { std::exit(0); }