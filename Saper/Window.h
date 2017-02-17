#pragma once

#include "ncurses.h"
#include "Color.h"
#include "Menu.h"
#include <list>
#include <string>
#include <array>
#include <thread>


/*!
*  \brief     Adapter klasy bibliotecznej ncurses
*  \details   Jest to klasa konwertujaca proceduralny interfejs (obslugujacy okna) biblioteki ncurses na interfejs obiektowy, o wiele wygodniejszy w uzyciu
*  \author    Mateusz Winiarski
*  \version   v1.0
*  \date      2015
*  \warning   Zaimplementowane tylko metody potrzebne w naszym projekcie
*/
class Window {
	public:
		/*!
		*  \brief     Konstruktor klasy Window
		*  \details   Tworzy obiekt okna, jesli podamy bez zadnych parametrow stworzy nam domyslny obiekt konsoli (odpowiadajacy stdscr w ncurses).
		*  @param lines, columns Wysokosc i szerokosc okna
		*  @param posLine, PosColumn Polozenie okna na ekranie
		*  @param window Wskaznik na okno jakie ma zostac opakowane
		*/
		Window(int lines = 0, int columns = 0, int posLine = 0, int posColumn = 0, WINDOW* window = NULL);

		/*!
		*  \brief     Destruktor klasy Window
		*  \details   Usuwaobiekt Window czyszczac jego atrybuty i usuwajac z pamieci okno.
		*/
		~Window();

		/*!
		*  \brief     Wyswietla tekst
		*  @param text Tekst do wyswietlenia
		*  \return Zwracany jest obiekt Window na ktorym jest wyswietlany tekst w celu umozliwienia kaskadowego wywolywania operatora <<.
		*/
		Window& operator<<(char* text);

		/*!
		*  \brief     Wyswietla tekst
		*  @param text Tekst do wyswietlenia
		*  \return Zwracany jest obiekt Window na ktorym jest wyswietlany tekst w celu umozliwienia kaskadowego wywolywania operatora <<.
		*/
		Window& operator<<(std::string text);

		/*!
		*  \brief     Wyswietla pojedynczy znak
		*  @param sign Znak do wyswietlenia
		*  \return Zwracany jest obiekt Window na ktorym jest wyswietlany znak w celu umozliwienia kaskadowego wywolywania operatora <<.
		*/
		Window& operator<<(char sign);

		/*!
		*  \brief     Wyswietla pojedynczy znak
		*  @param sign Znak do wyswietlenia
		*  \return Zwracany jest obiekt Window na ktorym jest wyswietlany znak w celu umozliwienia kaskadowego wywolywania operatora <<.
		*/
		Window& operator<<(const unsigned char sign);

		/*!
		*  \brief     Wyswietla pojedynczy znak
		*  @param sign Znak do wyswietlenia
		*  \return Zwracany jest obiekt Window na ktorym jest wyswietlany znak w celu umozliwienia kaskadowego wywolywania operatora <<.
		*/
		Window& operator<<(wchar_t sign);

		/*!
		*  \brief     Wyswietla pojedynczy znak
		*  @param sign Znak do wyswietlenia
		*  \return Zwracany jest obiekt Window na ktorym jest wyswietlany znak w celu umozliwienia kaskadowego wywolywania operatora <<.
		*/
		Window& operator<<(chtype sign);

		/*!
		*  \brief     Wyswietla pojedynczy znak
		*  @param sign Znak do wyswietlenia
		*  \return Zwracany jest obiekt Window na ktorym jest wyswietlany znak w celu umozliwienia kaskadowego wywolywania operatora <<.
		*/
		Window& operator<<(chtype* sign);

		/*!
		*  \brief     Wyswietla liczba calkowita
		*  @param number Liczba do wyswietlenia
		*  \return Zwracany jest obiekt Window na ktorym jest wyswietlana liczba w celu umozliwienia kaskadowego wywolywania operatora <<.
		*/
		Window& operator<<(int number);

		/*!
		*  \brief     Wyswietla liczba calkowita bez znaku
		*  @param number Liczba do wyswietlenia
		*  \return Zwracany jest obiekt Window na ktorym jest wyswietlana liczba w celu umozliwienia kaskadowego wywolywania operatora <<.
		*/
		Window& operator<<(unsigned int number);

		/*!
		*  \brief     Wyswietla liczba zmiennoprzecinkowa
		*  @param number Liczba do wyswietlenia
		*  \return Zwracany jest obiekt Window na ktorym jest wyswietlana liczba w celu umozliwienia kaskadowego wywolywania operatora <<.
		*/
		Window& operator<<(double number);

		/*!
		*  \brief     Wyswietla menu
		*  @param menu Menu do wyswietlenia
		*  \return Zwracany jest obiekt Window na ktorym jest wyswietlane menu w celu umozliwienia kaskadowego wywolywania operatora <<.
		*/
		Window& operator<<(Menu& menu);

		/*!
		*  \brief     Wyswietla pojedynczy wpis z menu
		*  @param entry Wpis z menu do wyswietlenia
		*  \return Zwracany jest obiekt Window na ktorym jest wyswietlany wpis z menu w celu umozliwienia kaskadowego wywolywania operatora <<.
		*/
		Window& operator<<(MenuEntry& entry);

		/*!
		*  \brief     Wczytywany jest tekst z konsoli
		*  @param text Zmienna do ktorej wczytujemy tekst
		*/
		void operator>>(char* text) { wgetstr(_window, text); }

		/*!
		*  \brief     Wczytywany jest pojedynczy znak z konsoli
		*  @param sign Zmienna do ktorej wczytujemy znak
		*/
		void operator>>(char& sign) { sign = wgetch(_window); }

		/*!
		*  \brief     Wczytywany jest pojedyncza liczbe z konsoli
		*  @param sign Zmienna do ktorej wczytujemy liczbe
		*/
		void operator>>(int& sign) { sign = wgetch(_window); }

		/*!
		*  \brief     Funkcja konwertujaca obiekt Window na biblioteczna reprezentacje WINDOW*
		*  \return Reprezentacja obiektu jako WINDOW*
		*/
		operator WINDOW*() { return _window; }

		/*!
		*  \brief     Funkcja konwertujaca obiekt Window na biblioteczna reprezentacje WINDOW
		*  \return Reprezentacja obiektu jako WINDOW
		*/
		operator WINDOW() { return *_window; }

		/*!
		*  \brief     Ustawiana jest widocznosc kursora
		*  @param isCurorVisible Zmienna reprezentujaca czy chcemy widziec kursor na ekranie w danym momencie czy nie.
		*/
		static void SetCursor(bool isCurorVisible) { curs_set(isCurorVisible); }

		/*!
		*  \brief     Ustawiany jest domyslny kolor tla i tekstu w konsoli
		*  @param colorPair Para kolorow (tekst, tlo) na jaki chcemy ustawic domyslne okno.
		*/
		static void AssumeDefaultColors(ColorPair colorPair);

		/*!
		*  \brief     Ustawiana jest widocznosc wpisywanych znakow w konsoli
		*  @param isCurorVisible Zmienna reprezentujaca czy chcemy widziec wpisywane znaki na ekranie w danym momencie czy nie.
		*/
		static void SetEcho(bool isActive);

		/*!
		*  \brief     Ustawiana jest pozycja kursora
		*  @param line,column Zmienna reprezentujaca pozycje ustawienia kursora
		*/
		void MoveCursor(int line, int column);

		/*!
		*  \brief     Wlaczany jest atrybut dla okna
		*  @param attrybute Atrybut ktory chcemy ustawic
		*/
		void AttrOn(chtype attrybute); 

		/*!
		*  \brief     Wylaczany jest atrybut dla okna
		*  @param attrybute Atrybut ktory chcemy usunac
		*/
		void AttrOff(chtype attrybute);

		/*!
		*  \brief     Odswierzanie okna. Powoduje wyczyszczenie bufora i wyswietlenie wszystkich zmian w oknie.
		*/
		void Refresh() { wrefresh(_window); }

		/*!
		*  \brief     Ustawiamy kolor tla
		*  @param attrybute Kolor tla jaki chcemy ustawic
		*/
		void Background(chtype attrybute);

		/*!
		*  \brief     Funkcja zwraca obecna pozycje kursora
		*  \return attrybute Pozycja kursora zapakowana w std::array
		*/
		std::array<int, 2>& GetCursorPos();

		/*!
		*  \brief     Zmiana wielkosci okna
		*  @param line,column Zmienna reprezentujaca nowe wymiary okna
		*/
		void Resize(int lines, int columns);

		/*!
		*  \brief     Funkcja zwraca ilosc linii w oknie
		*  \return ilosc linii w oknie
		*/
		int lines() { return _lines; }

		/*!
		*  \brief     Funkcja zwraca ilosc kolumn w oknie
		*  \return ilosc kolumn w oknie
		*/
		int columns() { return _columns; }

		/*!
		*  \brief     Funkcja zwraca pozycje X okna
		*  \return Pozycja X okna
		*/
		int x() { return _x; }

		/*!
		*  \brief     Funkcja zwraca pozycje Y okna
		*  \return Pozycja Y okna
		*/
		int y() { return _y; }

		/*!
		*  \brief     Funkcja pobierajaca z obiekt Window jego biblioteczna reprezentacje czyli WINDOW*
		*  \return Reprezentacja obiektu jako WINDOW*
		*/
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