#pragma once
#include <map>
#include <string>
#include <vector>
/*!
*  \brief     Klasa Wyświetlająca tekst pomocy
*  \details   Jest to klasa wyświetlająca instrukjce sterowania i gry w Sapera
*  \author    Magdalena Wieczorek
*  \version   v1.0
*  \date      2015
*/
class Help {
	public:
		/*!
		*  \brief     Funkcja wyświetlająca tekst pomocy
		*/
		static void View();
private:
	static bool show;
};
