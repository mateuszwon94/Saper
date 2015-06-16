#pragma once

#include <string>

typedef void(*action)();

/*!
*  \brief     Klasa obslugujaca pojedyncza pozycje w menu
*  \details   Jest to klasa zajmujaca sie wszystkimi czynnosciami jakie moze wykonac pojedynczy wpis w menu
*  \author    Mateusz Winiarski
*  \version   v1.0
*  \date      2015
*/
class MenuEntry {
	public:
		/*!
		*  \brief     Konstruktor klasy MenuEntry
		*  @param name String zawierajacy opis przycisku
		*  @param function Funkcja przypisana przyciskowi
		*  @param special Zmienna zawierajaca ktore z liter w danym wpisie jest wyrozniona
		*  @param isActive Zmienna reprezentujaca czy mozna wejsc w interakcje z danym przyciskiem 
		*/
		MenuEntry(std::string name, action function, int special = 0, bool isActive = true) : _name(name), _special(special), _isActive(isActive), _function(function) { }

		/*!
		*  \brief     Funkcja zwracajace napis reprezentujacy przycisk
		*  \return    Napis reprezentujacy przycisk
		*/
		std::string& Name() { return _name; }

		/*!
		*  \brief     Funkcja zwracajace indeks znaku specjalnego
		*  \return    Indeks znaku specjalnego
		*/
		int Special() { return _special; }

		/*!
		*  \brief     Funkcja konwertujaca MenuEntry na zmienna typu bool
		*  \return    Czy MenuEntry jest aktywne
		*/
		operator bool() { return _isActive; }

		/*!
		*  \brief     Funkcja zmieniajaca aktywnosc danego MenuEntry
		*/
		void ChangeActive() { _isActive = !_isActive; }

		/*!
		*  \brief     Funkcja wolajaca funkcje ktora jest przypisana do konkretnego MenuEntry
		*/
		void operator()() { _function(); }

	private:
		std::string _name;
		int _special = 0;
		bool _isActive;
		void(*_function)();
};