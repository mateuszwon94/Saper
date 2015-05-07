#include "Menu.h"
#include "Window.h"
#include <cstdarg>

using namespace std;

array<int, 3> EASY = { 8,8,10 };
array<int, 3> NORMAL = { 16,16,40 };
array<int, 3> HARD = { 30,16,99 };

int Menu::_columns = 8;
int Menu::_lines = 8;
int Menu::_bombs = 10;

Menu::Menu(std::vector<std::string> entrys, std::vector<action> functions, std::vector<int> specials, unsigned int line, unsigned int column, bool visibility) {
	if (entrys.size() < specials.size()) {
		for (int i = entrys.size(); i < specials.size(); ++i)
			specials.push_back(0);
	}
	for (int i = 0; i < entrys.size(); ++i) {
		if (entrys[i] == "Kontynuuj") 
			_entrys.push_back(MenuEntry(entrys[i], functions[i], specials[i], true));
		else
			_entrys.push_back(MenuEntry(entrys[i], functions[i], specials[i]));
	}
		
		
	_posLine = line;
	_posColumn = column;
	_visible = visibility;
}

void Menu::MoveUp() {
	if (_currEntry == 0)
		_currEntry = _entrys.size() - 1;
	else
		--_currEntry;
}

void Menu::MoveDown() {
	if (_currEntry == _entrys.size() - 1)
		_currEntry = 0;
	else
		++_currEntry;
}

void Menu::Move(int sign, Window& console, Window& gameWindow) {
	bool isSet = false;
	switch (sign) {
		case 27:
			SetCurrentEntry(_entrys.size() - 1);
			isSet = true;
			break;
		case KEY_UP:
			MoveUp(); 
			isSet = true;
			break;
		case KEY_DOWN:
			MoveDown();
			isSet = true;
			break;
		case '\n':
		case '\r':
		case ' ':
			CallCurrentFunction(gameWindow);
			isSet = true;
			break;
	}

	if (!isSet) {
		int i = 0;
		for (MenuEntry& entry : _entrys) {
			if (sign == entry.Name()[entry.Special()] || sign == entry.Name()[entry.Special()] + 32 || sign == entry.Name()[entry.Special()] - 32 || sign == i + 49) {
				SetCurrentEntry(i);
			}
			++i;
		}
	}

	MoveCursor(console, gameWindow);
}

void Menu::MoveCursor(Window& console, Window& gameWindow) {
	console.MoveCursor(gameWindow.x() + PosLine() + CurrentEntry() * 2, gameWindow.y() + PosColumn() + _entrys[CurrentEntry()].Special() +3);
}

void Menu::CallCurrentFunction(Window& gameWindow) {
	switch (_currEntry) {
		case 0:
			setMode(EASY);
			RefreshCLB(gameWindow);
			break;
		case 1:
			setMode(NORMAL);
			RefreshCLB(gameWindow);
			break;
		case 2:
			setMode(HARD);
			RefreshCLB(gameWindow);
			break;
		case 3:
			setCustmMode();
			break;

	}
	_entrys[_currEntry]();
}

void Menu::setMode(std::array<int, 3> mode) {
	_columns = mode[0];
	_lines = mode[1];
	_bombs = mode[2];
}

void Menu::RefreshCLB(Window & gameWindow) {
	gameWindow.MoveCursor(_posLine + 2 * _entrys.size() + 2, _posColumn+9);
	gameWindow << "   ";
	gameWindow.MoveCursor(_posLine + 2 * _entrys.size() + 2, _posColumn);
	gameWindow << "Kolumny: " << _columns;
	gameWindow.MoveCursor(_posLine + 2 * _entrys.size() + 4, _posColumn+9);
	gameWindow << "   ";
	gameWindow.MoveCursor(_posLine + 2 * _entrys.size() + 4, _posColumn);
	gameWindow << "Wiersze: "<< _lines;
	gameWindow.MoveCursor(_posLine + 2 * _entrys.size() + 6, _posColumn+9);
	gameWindow << "   ";
	gameWindow.MoveCursor(_posLine + 2 * _entrys.size() + 6, _posColumn);
	gameWindow << "Bomby:   " << _bombs;
}


