#pragma once

#include "MenuEntry.h"
#include <array>
#include <vector>
#include <string>

class Window;

/*!
*  \brief     Klasa obslugujaca menu
*  \details   Jest to klasa zajmujaca sie obsluga menu w grze. Ustawia poziom, uruchamia gra, wyswietla wyniki czy pomoc oraz konczy program
*  \author    Mateusz Winiarski
*  \version   v1.0
*  \date      2015
*/
class Menu {
	public:
		/*!
		*  \brief     Konstruktor klasy Menu
		*  @param entrys Vector zawierajacy opis przyciskow
		*  @param functions Vector zawierajacy funkcje przypisane odpowiednim przyciskom
		*  @param specials Vector zawierajacy ktore z liter w danym wpisie jest wyrozniona
		*  @param line,column Pozycja w jakiej Menu bedzie wyswietlane
		*  @param visibility Zmienna reprezentujaca czy menu bedzie wyswietlane
		*/
		Menu(std::vector<std::string> entrys, std::vector<void(*)()> functions, std::vector<int> specials = { }, unsigned int line = 0, unsigned int column = 0, bool visibility = true);

		/*!
		*  \brief     Typedef definiujacy czym jest w tej klasie Iterator
		*/
		typedef MenuEntry* Iterator;

		/*!
		*  \brief     Funkcja zwracajaca Iterator na pierwszy element Menu
		*  \details   Wykorzystywana w ranged base for loop
		*  \return    Iterator na pierwszy element Menu
		*/
		Iterator begin() { return &_entrys[0]; }

		/*!
		*  \brief     Funkcja zwracajaca Iterator na miejsca za ostatnim elementem Menu
		*  \details   Wykorzystywana w ranged base for loop
		*  \return    Iterator na miejsca za ostatnim elementem Menu
		*/
		Iterator end() { return (&_entrys[size()-1])+1; }
		
		/*!
		*  \brief     Funkcja zwracajaca MenuEntry spod konkretnego indeksu
		*  @param count Indeks spod ktorego ma byc zwrucone MenuEntry
		*  \return    MenuEntry spod indeksu count
		*/
		MenuEntry& operator[](unsigned int count) { return _entrys[count]; }

		/*!
		*  \brief     Funkcja ustawiajaca MenuEntry spod konkretnego indeksu na aktywne
		*  @param count Indeks spod ktorego MenuEntry ma byc ustawione na aktywne
		*/
		void setActive(unsigned int i);

		/*!
		*  \brief     Funkcja podajaca rozmiar Menu
		*  \return    Ilosc elementow w Menu
		*/
		size_t size() { return _entrys.size(); }

		/*!
		*  \brief     Funkcja podajaca poczatkowa linie Menu
		*  \return    Poczatkowa linia Menu
		*/
		unsigned int PosLine() { return _posLine; }

		/*!
		*  \brief     Funkcja podajaca poczatkowa kolumne Menu
		*  \return    Poczatkowa kolumna Menu
		*/
		unsigned int PosColumn() { return _posColumn; }

		/*!
		*  \brief     Funkcja ustawiajaca obecnie aktywne MenuEntry na zadane
		*  @param which Ktore MenuEntry ma byc ustawione na aktywne
		*/
		void SetCurrentEntry(int which);

		/*!
		*  \brief     Funkcja zajmujaca sie przesuwaniem po Menu
		*  @param sign Przechwyycony klawisz z klawiatury
		*/
		void Move(int sign);

		/*!
		*  \brief     Funkcja zajmujaca sie przesuwaniem po Menu kursora
		*/
		void MoveCursor();

		/*!
		*  \brief     Funkcja zajmujaca sie wywolaniem odpowiedniej funkcji dla obecnego MenuEntry
		*/
		void CallCurrentFunction();

		/*!
		*  \brief     Funkcja zwracajaca obecnie ustalona liczbe kolumne
		*  \return    Obecna liczba kolumn
		*/
		static int getColumns() { return _columns; }

		/*!
		*  \brief     Funkcja zwracajaca obecnie ustalona liczbe wierszy
		*  \return    Obecna liczba wierszy
		*/
		static int getLines() { return _lines; }

		/*!
		*  \brief     Funkcja zwracajaca obecnie ustalona liczbe bomb
		*  \return    Obecna liczba bomb
		*/
		static int getBombs() { return _bombs; }

		/*!
		*  \brief     Funkcja odswierzajaca wyswietlana liczbe kolumn wierszy i bomb
		*/
		void RefreshCLB();

		/*!
		*  \brief     Funkcja zwracajaca obecna instancje Menu
		*  \return    Obecnie uzywana instancja Menu
		*/
		static Menu& current() { return *_menu; }

	private:
		int CurrentEntry() { return _currEntry; }
		void MoveUp();
		void MoveDown();
		void setCustmMode();
		void setMode(std::array<int, 3> mode);
		void setCLB(int number, int which, std::array<std::string, 3>& svars);

		std::vector<MenuEntry> _entrys = std::vector<MenuEntry>();
		int _currEntry = 0;
		unsigned int _posLine = 0;
		unsigned int _posColumn = 0;
		bool _visible = true;
		static int _columns;
		static int _lines;
		static int _bombs;

		static Menu* _menu;
};
