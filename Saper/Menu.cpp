#include "Menu.h"
#include "Window.h"
#include "Timer.h"
#include <cstdarg>

using namespace std;

Menu* Menu::_menu = nullptr;

array<int, 3> EASY = { 8,8,10 };
array<int, 3> NORMAL = { 16,16,40 };
array<int, 3> HARD = { 30,16,99 };

int Menu::_columns = 8;
int Menu::_lines = 8;
int Menu::_bombs = 10;

Menu::Menu(std::vector<std::string> entrys, std::vector<void(*)()> functions, std::vector<int> specials, unsigned int line, unsigned int column, bool visibility) {
	if (entrys.size() < specials.size()) {
		for (int i = entrys.size(); i < specials.size(); ++i)
			specials.push_back(0);
	}
	for (int i = 0; i < entrys.size(); ++i) {
		if (i == 5) 
			_entrys.push_back(MenuEntry(entrys[i], functions[i], specials[i], false));
		else
			_entrys.push_back(MenuEntry(entrys[i], functions[i], specials[i]));
	}
		
		
	_posLine = line;
	_posColumn = column;
	_visible = visibility;

	if (_menu != nullptr)
		delete _menu;
	_menu = this;
}

void Menu::setActive(unsigned int i) {
	_entrys[i].ChangeActive();
	gameWindow << *this;
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
			if (_currEntry == _entrys.size() - 1) _entrys[_currEntry]();
			SetCurrentEntry(_entrys.size() - 1);
			isSet = true;
			break;
		case KEY_UP:
			do {
				MoveUp();
			} while (!_entrys[_currEntry]);
			isSet = true;
			break;
		case KEY_DOWN:
			do {
				MoveDown();
			} while (!_entrys[_currEntry]);
			isSet = true;
			break;
		case '\n':
		case '\r':
		case ' ':
			CallCurrentFunction(console,gameWindow);
			isSet = true;
			break;
	}

	if (!isSet) {
		int i = 0;
		for (MenuEntry& entry : _entrys) {
			if (sign == entry.Name()[entry.Special()] || sign == entry.Name()[entry.Special()] + 32 || sign == entry.Name()[entry.Special()] - 32 || sign == i + 49) {
				SetCurrentEntry(i);
				break;
			}
			++i;
		}
	}

	MoveCursor(console, gameWindow);
}

void Menu::MoveCursor(Window& console, Window& gameWindow) {
	Timer::getMutex()->lock();
	console.MoveCursor(gameWindow.x() + PosLine() + CurrentEntry() * 2, gameWindow.y() + PosColumn() + _entrys[CurrentEntry()].Special() +3);
	Timer::getMutex()->unlock();
}

void Menu::CallCurrentFunction(Window& console, Window& gameWindow) {
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
			setCustmMode(console,gameWindow);
			setMode({_columns,_lines,_bombs });
			RefreshCLB(gameWindow);
			break;

	}
	_entrys[_currEntry]();
}

void Menu::setCustmMode(Window & console, Window & gameWindow) {
	Timer::getMutex()->lock();
	static ColorPair error = ColorPair(COLOR_RED, COLOR_WHITE);
	static char mult = 158;
	array<int*, 3> vars = { &_columns, &_lines, &_bombs };
	array<string, 3> svars = { "0","0","0" };
	for (int* var : vars)
		*var = 0;
	RefreshCLB(gameWindow);
	int which = 0;
	int posx = _posLine + 4 + 2 * _entrys.size() + 2;
	int posy = _posColumn + 9;
	int sign;
	console.MoveCursor(gameWindow.x() + posx - 4 + 2 * which, gameWindow.y() + posy);
	
	gameWindow.MoveCursor(posx + 4, _posColumn - 2);
	gameWindow << "Nacisnij [ENTER],";
	gameWindow.MoveCursor(posx + 5, _posColumn - 2);
	gameWindow << "zeby zatwierdzic.";
	gameWindow.MoveCursor(posx + 7, _posColumn - 2);
	gameWindow << "Max kolumn to 70";
	gameWindow.MoveCursor(posx + 8, _posColumn - 2);
	gameWindow << "Max wierszy to 40";
	gameWindow.MoveCursor(posx + 9, _posColumn - 2);
	gameWindow << "Max bomb to K" << mult << "W-1";
	
	gameWindow.MoveCursor(posx-4 + 2 * which, posy);
	while (true) {
		console >> sign;
		switch (sign) {
			case KEY_UP:
				if (which == 0) which = 2;
				else --which;
				console.MoveCursor(gameWindow.x() + posx - 4 + 2 * which, gameWindow.y() + posy);
				gameWindow.MoveCursor(posx -4+ 2 * which, posy);
				break;
			case KEY_DOWN:
				if (which == 2) which = 0;
				else ++which;
				console.MoveCursor(gameWindow.x() + posx - 4 + 2 * which, gameWindow.y() + posy);
				gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
				break;
			case '1':
				if (svars[which].length() <= 2) {
					svars[which] += "1";
					gameWindow << '1';
				}
				break;
			case '2':
				if (svars[which].length() <= 2) {
					svars[which] += "2";
					gameWindow << '2';
				}
				break;
			case '3':
				if (svars[which].length() <= 2) {
					svars[which] += "3";
					gameWindow << '3';
				}
				break;
			case '4':
				if (svars[which].length() <= 2) {
					svars[which] += "4";
					gameWindow << '4';
				}
				break;
			case '5':
				if (svars[which].length() <= 2) {
					svars[which] += "5";
					gameWindow << '5';
				}
				break;
			case '6':
				if (svars[which].length() <= 2) {
					svars[which] += "6";
					gameWindow << '6';
				}
				break;
			case '7':
				if (svars[which].length() <= 2) {
					svars[which] += "7";
					gameWindow << '7';
				}
				break;
			case '8':
				if (svars[which].length() <= 2) {
					svars[which] += "8";
					gameWindow << '8';
				}
				break;
			case '9':
				if (svars[which].length() <= 2) {
					svars[which] += "9";
					gameWindow << '9';
				}
				break;
			case '0':
				if (svars[which].length() <= 2) {
					svars[which] += "0";
					gameWindow << '0';
				}
				break;
			case '\b':
			case KEY_BACKSPACE:
				gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
				gameWindow << "    ";
				gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
				svars[which] = "0";
				break;
			case 27:
				setMode(EASY);
				RefreshCLB(gameWindow);
				gameWindow.MoveCursor(posx + 4, _posColumn - 2);
				gameWindow << "                 ";
				gameWindow.MoveCursor(posx + 5, _posColumn - 2);
				gameWindow << "                 ";
				gameWindow.MoveCursor(posx + 7, _posColumn - 2);
				gameWindow << "                 ";
				gameWindow.MoveCursor(posx + 8, _posColumn - 2);
				gameWindow << "                 ";
				gameWindow.MoveCursor(posx + 9, _posColumn - 2);
				gameWindow << "                 ";
				gameWindow.MoveCursor(posx + 13, _posColumn - 2);
				gameWindow << "                  ";
				return;
			case KEY_ENTER:
			case '\n':
			case '\r':
				for (int i = 0; i < 3; ++i)
					*vars[i] = stoi(svars[i]);
				if (0 >= *vars[0] || *vars[0] > 70) {
					gameWindow.MoveCursor(posx + 13, _posColumn - 2);
					gameWindow << "                  ";
					gameWindow.MoveCursor(posx + 13, _posColumn - 2);
					gameWindow.AttrOn(A_BOLD);
					gameWindow.AttrOn(error);
					gameWindow << "Zla liczba kolumn";
					gameWindow.AttrOff(error);
					gameWindow.AttrOff(A_BOLD);
					gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
					continue;
				} else if (0 >= *vars[1] || *vars[1] > 40) {
					gameWindow.MoveCursor(posx + 13, _posColumn - 2);
					gameWindow << "                  ";
					gameWindow.MoveCursor(posx + 13, _posColumn - 2);
					gameWindow.AttrOn(A_BOLD);
					gameWindow.AttrOn(error);
					gameWindow << "Zla liczba wierszy";
					gameWindow.AttrOff(error);
					gameWindow.AttrOff(A_BOLD);
					gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
					continue;
				} else if (0 >= *vars[2] || *vars[2] > *vars[0] * (*vars[1]) - 1) {
					gameWindow.MoveCursor(posx + 13, _posColumn - 2);
					gameWindow << "                  ";
					gameWindow.MoveCursor(posx + 13, _posColumn - 2);
					gameWindow.AttrOn(A_BOLD);
					gameWindow.AttrOn(error);
					gameWindow << "Zla liczba bomb";
					gameWindow.AttrOff(error);
					gameWindow.AttrOff(A_BOLD);
					gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
					continue;
				}
				gameWindow.MoveCursor(posx + 4, _posColumn - 2);
				gameWindow << "                 ";
				gameWindow.MoveCursor(posx + 5, _posColumn - 2);
				gameWindow << "                 ";
				gameWindow.MoveCursor(posx + 7, _posColumn - 2);
				gameWindow << "                 ";
				gameWindow.MoveCursor(posx + 8, _posColumn - 2);
				gameWindow << "                 ";
				gameWindow.MoveCursor(posx + 9, _posColumn - 2);
				gameWindow << "                 ";
				gameWindow.MoveCursor(posx + 13, _posColumn - 2);
				gameWindow << "                  ";
				return;
		}
	}
	Timer::getMutex()->unlock();
}

void Menu::setMode(std::array<int, 3> mode) {
	_columns = mode[0];
	_lines = mode[1];
	_bombs = mode[2];
}

void Menu::RefreshCLB(Window & gameWindow) {
	Timer::getMutex()->lock();
	gameWindow.MoveCursor(_posLine + 2 * _entrys.size() + 2, _posColumn+9);
	gameWindow << "   ";
	gameWindow.MoveCursor(_posLine + 2 * _entrys.size() + 2, _posColumn);
	gameWindow << "Kolumny: ";
	if (_columns)
		gameWindow << _columns;
	else
		gameWindow << "   ";
	gameWindow.MoveCursor(_posLine + 2 * _entrys.size() + 4, _posColumn+9);
	gameWindow << "   ";
	gameWindow.MoveCursor(_posLine + 2 * _entrys.size() + 4, _posColumn);
	gameWindow << "Wiersze: ";
	if (_lines)
		gameWindow << _lines;
	else
		gameWindow << "   ";
	gameWindow.MoveCursor(_posLine + 2 * _entrys.size() + 6, _posColumn+9);
	gameWindow << "   ";
	gameWindow.MoveCursor(_posLine + 2 * _entrys.size() + 6, _posColumn);
	gameWindow << "Bomby:   ";
	if (_bombs)
		gameWindow << _bombs;
	else
		gameWindow << "   ";
	Timer::getMutex()->unlock();
}