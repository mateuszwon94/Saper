#pragma once

#include "ncurses.h"
#include "Color.h"
#include "Menu.h"
#include <list>
#include <string>

class Window {
	public:
		Window(int lines = 0, int columns = 0, int posLine = 0, int posColumn = 0, WINDOW* window = NULL);
		~Window();

		Window& operator<<(char* text);
		Window& operator<<(std::string text);
		Window& operator<<(char sign);
		Window& operator<<(const unsigned char sign);
		Window& operator<<(wchar_t sign);
		Window& operator<<(chtype sign);
		Window& operator<<(chtype* sign);
		Window& operator<<(int number);
		Window& operator<<(double number);
		Window& operator<<(Menu& menu);
		Window& operator<<(MenuEntry& entry);

		void operator>>(char* text) { wgetstr(_window, text); }
		void operator>>(char& sign) { sign = wgetch(_window); }
		void operator>>(int& sign) { sign = wgetch(_window); }

		operator WINDOW*() { return _window; }
		operator WINDOW() { return *_window; }

		static void SetCursor(bool isCurorVisible) { curs_set(isCurorVisible); }

		static void AssumeDefaultColors(int text, int background);
		static void AssumeDefaultColors(ColorPair colorPair);

		static void SetEcho(bool isActive);

		void MoveCursor(int line, int column);
		void MoveWindow(int line, int column);
		void AttrOn(chtype attrybute); 
		void AttrOff(chtype attrybute);
		void Refresh() { wrefresh(_window); }
		void Background(chtype attrybute);
		void SetBorder(chtype leftSide, chtype rightSide, chtype topSide, chtype bottomSide, chtype topLeftCorner, chtype topRightCorner, chtype bottomLeftCorner, chtype bottomRightCorner);
		void SetBorder(chtype* leftSide = WACS_VLINE, chtype* rightSide = WACS_VLINE, chtype* topSide = WACS_HLINE, chtype* bottomSide = WACS_HLINE, chtype* topLeftCorner = WACS_ULCORNER, chtype* topRightCorner = WACS_URCORNER, chtype* bottomLeftCorner = WACS_LLCORNER, chtype* bottomRightCorner = WACS_LRCORNER);
		void SetBorder(char leftSide, char rightSide, char topSide, char bottomSide, char topLeftCorner, char topRightCorner, char bottomLeftCorner, char bottomRightCorner);

		void Resize(int lines, int columns);

		int lines() { return _lines; }
		int columns() { return _columns; }

		int x() { return _x; }
		int y() { return _y; }

		WINDOW *getWin();
	protected:
		static int count;
		WINDOW* _window;
		int _x;
		int _y;
		int _lines;
		int _columns;
		std::list<chtype> _attrybutes = std::list<chtype>();
};

extern Window& console;
extern Window& gameWindow;
extern Window& shadow;