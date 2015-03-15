#ifndef WINDOW_H
#define WINDOW_H

#include "ncurses.h"
#include "Color.h"
#include <list>

class Window {
	public:
		Window(int lines = 0, int columns = 0, int x = 0, int y = 0, WINDOW* window = NULL);
		~Window();

		Window& operator<<(char* text);
		Window& operator<<(char sign);
		Window& operator<<(int number);
		Window& operator<<(double number);

		void operator>>(char* text);
		void operator>>(char& sign);

		operator WINDOW*();

		static void SetCursor(bool isCurorVisible);

		static void AssumeDefaultColors(int text, int background);
		static void AssumeDefaultColors(ColorPair colorPair);

		static void SetEcho(bool isActive);

		void MoveCursor(int x, int y);
		void MoveWindow(int x, int y);
		void AttrOn(chtype attrybute); 
		void AttrOff(chtype attrybute);
		void Refresh();
		void Background(chtype attrybute);
		void SetBorder(chtype leftSide, chtype rightSide, chtype topSide, chtype bottomSide, chtype topLeftCorner, chtype topRightCorner, chtype bottomLeftCorner, chtype bottomRightCorner);
		void SetBorder(chtype* leftSide = WACS_VLINE, chtype* rightSide = WACS_VLINE, chtype* topSide = WACS_HLINE, chtype* bottomSide = WACS_HLINE, chtype* topLeftCorner = WACS_ULCORNER, chtype* topRightCorner = WACS_URCORNER, chtype* bottomLeftCorner = WACS_LLCORNER, chtype* bottomRightCorner = WACS_LRCORNER);
		void SetBorder(char leftSide, char rightSide, char topSide, char bottomSide, char topLeftCorner, char topRightCorner, char bottomLeftCorner, char bottomRightCorner);
		
		int lines() { return _lines; }
		int columns() { return _columns; }

		int x() { return _x; }
		int y() { return _y; }
	protected:
		WINDOW* _window;
		int _x;
		int _y;
		int _lines;
		int _columns;
		std::list<chtype> _attrybutes = std::list<chtype>();
		std::list<Window> _subWindow = std::list<Window>();
};

extern Window console;

#endif
