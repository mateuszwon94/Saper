#pragma once
#include <map>
#include <string>
#include <vector>
/*!
*  \brief     Klasa Wyœwietlaj¹ca tekst pomocy
*  \details   Jest to klasa wyœwietlaj¹ca instrukjce sterowania i gry w Sapera
*  \author    Magdalena Wieczorek
*  \version   v1.0
*  \date      2015
*/
class Help {
	public:
		/*!
		*  \brief     Funkcja wyœwietlaj¹ca tekst pomocy
		*/
		static void View();
private:
	static bool show;
};
