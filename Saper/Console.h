#ifndef CONSOLE_H
#define CONSOLE_H

#include "ncurses.h"
#include "Color.h"
#include <list>

class Console {
	public:
	//konstruktor domyœlny inicjalizuje wszystkie potrzebne rzeczy
		Console();
		//destruktor dezaktywuje wszystkie potrzebne rzeczy
		~Console();

		//przeladowany oparator << wiadomo po co :P
		Console& operator<<(char* text);
		Console& operator<<(int number);
		Console& operator<<(double number);

		//funkcja odswierzajaca ekran
		void Refresh();

		//funkcja przesuwajaca wskaznik pisania
		void MoveCurosor(int x, int y);

		//funkcja aktywujaca atrybut
		void AttrOn(chtype attrybute);

		//funkcja dezaktywujaca atrybut
		void AttrOff(chtype attrybute);

		//funkcja ustawiajaca widocznosc wskaznika pisania
		void CursSet(bool isCurorVisible);

		//funkcja ustawiajaca defaultowy kolor w terminalu
		void AssumeDefaultColors(int text, int background);
		void AssumeDefaultColors(ColorPair colorPair);

		void BorderSet(chtype leftSide, chtype rightSide, chtype topSide, chtype bottomSide, chtype topLeftCorner, chtype topRightCorner, chtype bottomLeftCorner, chtype bottomRightCorner);
		void BorderSet(chtype* leftSide = WACS_VLINE, chtype* rightSide = WACS_VLINE, chtype* topSide = WACS_HLINE, chtype* bottomSide = WACS_HLINE, chtype* topLeftCorner = WACS_ULCORNER, chtype* topRightCorner = WACS_URCORNER, chtype* bottomLeftCorner = WACS_LLCORNER, chtype* bottomRightCorner = WACS_LRCORNER);
		void BorderSet(char leftSide, char rightSide, char topSide, char bottomSide, char topLeftCorner, char topRightCorner, char bottomLeftCorner, char bottomRightCorner);

		//zwraca ilosc kolumn terminala
		int columns() { return _columns; }

		//zwraca ilosc wierszy terminala
		int lines() { return _lines; }
	protected:
		int _columns;
		int _lines;
		std::list<chtype> _attrybutes = std::list<chtype>();

};

extern Console console;

#endif
