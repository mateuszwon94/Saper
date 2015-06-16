#pragma once
#include <map>
#include <string>
#include <vector>
/*!
*  \brief     Klasa Wy�wietlaj�ca tekst pomocy
*  \details   Jest to klasa wy�wietlaj�ca instrukjce sterowania i gry w Sapera
*  \author    Magdalena Wieczorek
*  \version   v1.0
*  \date      2015
*/
class Help {
	public:
		/*!
		*  \brief     Funkcja wy�wietlaj�ca tekst pomocy
		*/
		static void View();
private:
	static bool show;
};
