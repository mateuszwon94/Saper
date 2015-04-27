#ifndef MENU_H
#define MENU_H

#include "MenuEntry.h"
#include <vector>
#include <string>

class Menu {
	public:
		Menu(std::vector<std::string> entrys, std::vector<int> specials, unsigned int line = 0, unsigned int column = 0, bool visibility = true);

		typedef MenuEntry* Iterator;

		Iterator begin() { return &_entrys[0]; }
		Iterator end() { return (&_entrys[size()-1])+1; }
		
		MenuEntry& operator[](unsigned int count) { return _entrys[count]; }

		int CurrentEntry() { return _currEntry; }
		size_t size() { return _entrys.size(); }
		unsigned int PosLine() { return _posLine; }
		unsigned int PosColumn() { return _posColumn; }
		bool IsVisible() { return _visible; }

		void SetCurrentEntry(int which = -1) { _currEntry = which; }
		void MoveUp();
		void MoveDown();

	private:
		std::vector<MenuEntry> _entrys = std::vector<MenuEntry>();
		int _currEntry = -1;
		unsigned int _posLine = 0;
		unsigned int _posColumn = 0;
		bool _visible = true;
};

#endif
