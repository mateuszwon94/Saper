#include "Menu.h"
#include <cstdarg>

using namespace std;

Menu::Menu(std::vector<std::string> entrys, std::vector<int> specials, unsigned int line, unsigned int column, bool visibility) {
	if (entrys.size() < specials.size()) {
		for (int i = entrys.size(); i < specials.size(); ++i)
			specials.push_back(0);
	}
	for (int i = 0; i < entrys.size(); ++i)
		_entrys.push_back(MenuEntry(entrys[i], specials[i]));
	_posLine = line;
	_posColumn = column;
	_visible = visibility;
}

void Menu::MoveUp() {
	if (_currEntry < 1)
		_currEntry = -1;
	else
		--_currEntry;
}

void Menu::MoveDown() {
	if (_currEntry > _entrys.size()-1)
		_currEntry = _entrys.size() - 1;
	else
		++_currEntry;
}