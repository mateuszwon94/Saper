#pragma once

#include "MenuEntry.h"
#include <array>
#include <vector>
#include <string>

class Window;

class Menu {
	public:
		Menu(std::vector<std::string> entrys, std::vector<void(*)()> functions, std::vector<int> specials = { }, unsigned int line = 0, unsigned int column = 0, bool visibility = true);

		typedef MenuEntry* Iterator;

		Iterator begin() { return &_entrys[0]; }
		Iterator end() { return (&_entrys[size()-1])+1; }
		
		MenuEntry& operator[](unsigned int count) { return _entrys[count]; }
		void setActive(unsigned int i);

		size_t size() { return _entrys.size(); }
		unsigned int PosLine() { return _posLine; }
		unsigned int PosColumn() { return _posColumn; }

		void SetCurrentEntry(int which) { _currEntry = which; }
		void MoveUp();
		void MoveDown();

		void Move(int sign, Window& console, Window& gameWindow);
		void MoveCursor(Window& console, Window& gameWindow);

		void CallCurrentFunction(Window& console, Window& gameWindow);

		static int getColumns() { return _columns; }
		static int getLines() { return _lines; }
		static int getBombs() { return _bombs; }

		void setCustmMode(Window& console, Window & gameWindow);

		void setMode(std::array<int, 3> mode);

		void RefreshCLB(Window& gameWindow);

		void setCLB(int number, int which, std::array<std::string, 3>& svars);

		static Menu& current() { return *_menu; }

	private:
		int CurrentEntry() { return _currEntry; }

		std::vector<MenuEntry> _entrys = std::vector<MenuEntry>();
		int _currEntry = 4;
		unsigned int _posLine = 0;
		unsigned int _posColumn = 0;
		bool _visible = true;
		static int _columns;
		static int _lines;
		static int _bombs;

		static Menu* _menu;
};
