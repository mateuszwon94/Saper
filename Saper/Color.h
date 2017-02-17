#pragma once

#include "ncurses.h"


/*!
*  \brief     Adapter klasy bibliotecznej ncurses
*  \details   Jest to klasa konwertujaca proceduralny interfejs (obslugujacy kolory) biblioteki ncurses na interfejs obiektowy, o wiele wygodniejszy w uzyciu
*  \author    Mateusz Winiarski
*  \version   v1.0
*  \date      2015
*  \warning   Zaimplementowane tylko metody potrzebne w naszym projekcie
*/
class ColorPair {
	public:
		/*!
		*  \brief     Konstruktor klasy ColorPair
		*  \details   Tworzy na podstawie zliczania ilosci wystapien nowa pare kolorow.
		*  @param text Reprezentacja koloru tekstu
		*  @param background Reprezentacja koloru tla
		*/
		ColorPair(short text, short background);

		/*!
		*  \brief     Funkcja konwertujaca oboekt typu ColorPair na biblioteczna reprezentacje
		*  \return    Biblioteczna reprezentacja obiektu
		*/
		operator chtype();

		/*!
		*  \brief     Funkcja zwracajaca biblioteczna reprezentacje koloru tekstu
		*  \return    Biblioteczna reprezentacae koloru tekstu
		*/
		short text() { return _text; }

		/*!
		*  \brief     Funkcja zwracajaca biblioteczna reprezentacje koloru tla
		*  \return    Biblioteczna reprezentacja koloru tla
		*/
		short background() { return _background; }
	private:
		static short count;
		short _text;
		short _background;
		short _number;
};

extern ColorPair textColor;
extern ColorPair specialTextColor;