#include "Menu.h"
#include "Window.h"
#include "Timer.h"
#include <cstdarg>
#include <stdexcept>

using namespace std;

Menu* Menu::_menu = nullptr;

array<int, 3> EASY = { 10,10,10 };
array<int, 3> NORMAL = { 15,15,35 };
array<int, 3> HARD = { 30,15,99 };

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
	array<string, 3> svars = { "","","" };
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
				gameWindow.MoveCursor(posx + 13, _posColumn - 3);
				gameWindow << "                   ";
				if (which == 0) which = 2;
				else --which;
				console.MoveCursor(gameWindow.x() + posx - 4 + 2 * which, gameWindow.y() + posy);
				gameWindow.MoveCursor(posx -4+ 2 * which, posy);
				break;
			case KEY_DOWN:
				gameWindow.MoveCursor(posx + 13, _posColumn - 3);
				gameWindow << "                   ";
				if (which == 2) which = 0;
				else ++which;
				console.MoveCursor(gameWindow.x() + posx - 4 + 2 * which, gameWindow.y() + posy);
				gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
				break;
			case '1':
				setCLB(1, which, svars);
				break;
			case '2':
				setCLB(2, which, svars);
				break;
			case '3':
				setCLB(3, which, svars);
				break;
			case '4':
				setCLB(4, which, svars);
				break;
			case '5':
				setCLB(5, which, svars);
				break;
			case '6':
				setCLB(6, which, svars);
				break;
			case '7':
				setCLB(7, which, svars);
				break;
			case '8':
				setCLB(8, which, svars);
				break;
			case '9':
				setCLB(9, which, svars);
				break;
			case '0':
				setCLB(0, which, svars);
				break;
			case '\b':
			case KEY_BACKSPACE:
				gameWindow.MoveCursor(posx + 13, _posColumn - 3);
				gameWindow << "                   ";
				gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
				gameWindow << "    ";
				gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
				svars[which] = "";
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
				gameWindow.MoveCursor(posx + 13, _posColumn - 3);
				gameWindow << "                   ";
				Timer::getMutex()->unlock();
				return;
			case KEY_ENTER:
			case '\n':
			case '\r':
				try {
					*vars[0] = stoi(svars[0]);
				} catch (invalid_argument& e) {
					gameWindow.MoveCursor(posx + 13, _posColumn - 3);
					gameWindow << "                   ";
					gameWindow.MoveCursor(posx + 13, _posColumn - 3);
					gameWindow.AttrOn(A_BOLD);
					gameWindow.AttrOn(error);
					gameWindow << "Zla liczba kolumn";
					gameWindow.AttrOff(error);
					gameWindow.AttrOff(A_BOLD);
					gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
					continue;
				}
				
				try {
					*vars[1] = stoi(svars[1]);
				} catch (invalid_argument& e) {
					gameWindow.MoveCursor(posx + 13, _posColumn - 3);
					gameWindow << "                   ";
					gameWindow.MoveCursor(posx + 13, _posColumn - 3);
					gameWindow.AttrOn(A_BOLD);
					gameWindow.AttrOn(error);
					gameWindow << "Zla liczba wierszy";
					gameWindow.AttrOff(error);
					gameWindow.AttrOff(A_BOLD);
					gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
					continue;
				}

				try {
					*vars[2] = stoi(svars[2]);
				} catch (invalid_argument& e) {
					gameWindow.MoveCursor(posx + 13, _posColumn - 3);
					gameWindow << "                   ";
					gameWindow.MoveCursor(posx + 13, _posColumn - 3);
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
				gameWindow.MoveCursor(posx + 13, _posColumn - 3);
				gameWindow << "                   ";
				Timer::getMutex()->unlock();
				return;
			default:
				gameWindow.MoveCursor(posx + 13, _posColumn - 3);
				gameWindow.AttrOn(A_BOLD);
				gameWindow.AttrOn(error);
				gameWindow << "Nieobslugiwany znak";
				gameWindow.AttrOff(error);
				gameWindow.AttrOff(A_BOLD);
				break;
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

void Menu::setCLB(int number, int which, array<string, 3>& svars) {
	static ColorPair error = ColorPair(COLOR_RED, COLOR_WHITE);

	int posx = _posLine + 4 + 2 * _entrys.size() + 2;
	int posy = _posColumn + 9;

	gameWindow.MoveCursor(posx + 13, _posColumn - 3);
	gameWindow << "                   ";

	if (which == 2) {
		int maxBombs;
		int bombsWanted;

		try {
			maxBombs = stoi(svars[0]) * stoi(svars[1]) - 1;
		} catch (invalid_argument& e) {
			gameWindow.MoveCursor(posx + 13, _posColumn - 3);
			gameWindow << "                   ";
			gameWindow.MoveCursor(posx + 13, _posColumn - 3);
			gameWindow.AttrOn(A_BOLD);
			gameWindow.AttrOn(error);
			gameWindow << "Brak kolumn/wierszy";
			gameWindow.AttrOff(error);
			gameWindow.AttrOff(A_BOLD);
			gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
			return;
		}

		try {
			bombsWanted = stoi(svars[2]) * 10 + number;
		} catch (invalid_argument& e) {
			bombsWanted = number;
		}

		if (0 >= bombsWanted || bombsWanted > maxBombs) {
			gameWindow.MoveCursor(posx + 13, _posColumn - 3);
			gameWindow << "                   ";
			gameWindow.MoveCursor(posx + 13, _posColumn - 3);
			gameWindow.AttrOn(A_BOLD);
			gameWindow.AttrOn(error);
			gameWindow << "Zla liczba bomb";
			gameWindow.AttrOff(error);
			gameWindow.AttrOff(A_BOLD);
			gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
			return;
		} else {
			gameWindow.MoveCursor(posx + 13, _posColumn - 3);
			gameWindow << "                   ";
			gameWindow.MoveCursor(posx - 4 + 2 * which, posy + svars[2].length());
			gameWindow << number;
			svars[2] += to_string(number);
		}
	} else if (which == 1) {
		int maxLines = 40;
		int linesWanted;
		try {
			linesWanted = stoi(svars[1]) * 10 + number;
		} catch (invalid_argument& e) {
			linesWanted = number;
		}

		if (1 >= linesWanted || linesWanted > maxLines) {
			gameWindow.MoveCursor(posx + 13, _posColumn - 3);
			gameWindow << "                   ";
			gameWindow.MoveCursor(posx + 13, _posColumn - 3);
			gameWindow.AttrOn(A_BOLD);
			gameWindow.AttrOn(error);
			gameWindow << "Zla liczba wierszy";
			gameWindow.AttrOff(error);
			gameWindow.AttrOff(A_BOLD);
			gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
			return;
		} else {
			gameWindow.MoveCursor(posx + 13, _posColumn - 3);
			gameWindow << "                   ";
			gameWindow.MoveCursor(posx - 4 + 2 * which, posy + svars[1].length());
			gameWindow << number;
			svars[1] += to_string(number);
		}
	} else if (which == 0) {
		int maxColumn = 70;
		int columnsWanted;
		try {
			columnsWanted = stoi(svars[0]) * 10 + number;
		} catch (invalid_argument e) {
			columnsWanted = number;
		}
		
		if (1 >= columnsWanted || columnsWanted > maxColumn) {
			gameWindow.MoveCursor(posx + 13, _posColumn - 3);
			gameWindow << "                   ";
			gameWindow.MoveCursor(posx + 13, _posColumn - 3);
			gameWindow.AttrOn(A_BOLD);
			gameWindow.AttrOn(error);
			gameWindow << "Zla liczba kolumn";
			gameWindow.AttrOff(error);
			gameWindow.AttrOff(A_BOLD);
			gameWindow.MoveCursor(posx - 4 + 2 * which, posy);
			return;
		} else {
			gameWindow.MoveCursor(posx + 13, _posColumn - 3);
			gameWindow << "                   ";
			gameWindow.MoveCursor(posx - 4 + 2 * which, posy + svars[0].length());
			gameWindow << number;
			svars[0] += to_string(number);
		}
	}

}