#pragma once
#include <map>
#include <string>
#include <vector>
/*!
*  \brief     Klasa Wyswietlajaca tekst pomocy
*  \details   Jest to klasa wyswietlajaca instrukjce sterowania i gry w Sapera
*  \author    Magdalena Wieczorek
*  \version   v1.0
*  \date      2015
*/
class Help {
	public:
		/*!
		*  \brief     Funkcja wyswietlajaca tekst pomocy
		*/
		static void View();
private:
	static bool show;
};
