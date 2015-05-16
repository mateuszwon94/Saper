#include "Help.h"
#include "Window.h"
#include <sstream>
#include <exception>
#include "Timer.h"

using namespace std;
bool Help::show = true;

void Help::View() {
	while(show) {
		Timer::getMutex()->lock();
		gameWindow.MoveCursor(1, 97);
		gameWindow.AttrOn(A_BOLD);
		static ColorPair green = ColorPair(COLOR_GREEN, COLOR_BLACK);
		gameWindow.AttrOn(green);
		gameWindow << "POMOC";
		gameWindow.AttrOff(green);
		gameWindow.AttrOff(A_BOLD);
		gameWindow.MoveCursor(3, 97);
		gameWindow << "Gra polega na odkrywaniu na planszy poszczegolnych pol, ";
		gameWindow.MoveCursor(4, 97);
		gameWindow << "w taki sposob, aby nie natrafic na mine. Na kazdym z odkrytych";
		gameWindow.MoveCursor(5, 97);
		gameWindow << "pol napisana jest liczba min, ktore bezposrednio stykaja sie";
		gameWindow.MoveCursor(6, 97);
		gameWindow << "z danym polem ( od 0 - pole puste, do 8 ). Jesli oznaczymy dane";
		gameWindow.MoveCursor(7, 97);
		gameWindow << "pole flaga, jest ono zabezpieczone przed odslonieciem,  ";
		gameWindow.MoveCursor(8, 97);
		gameWindow << "dzieki czemu przez przypadek nie odslonimy miny. ";
		gameWindow.MoveCursor(11, 97);
		gameWindow << "Sterowanie:";
		gameWindow.MoveCursor(13, 97);
		gameWindow << "[W] [8] [strzalka w gore]  - przemieszczanie sie w gore";
		gameWindow.MoveCursor(14, 97);
		gameWindow << "[X] [2] [strzalka w dol]   - poruszanie sie w dol";
		gameWindow.MoveCursor(15, 97);
		gameWindow << "[A] [4] [strzalka w lewo]  - poruszanie sie w lewo";
		gameWindow.MoveCursor(16, 97);
		gameWindow << "[D] [6] [strzalka w prawo] - poruszanie sie w prawo";
		gameWindow.MoveCursor(17, 97);
		gameWindow << "[Q] [7]                    - poruszanie sie na skos gora-lewo";
		gameWindow.MoveCursor(18, 97);
		gameWindow << "[E] [9]                    - poruszanie sie na skos gora-prawo";
		gameWindow.MoveCursor(19, 97);
		gameWindow << "[Z] [1]                    - poruszanie sie na skos dol-lewo";
		gameWindow.MoveCursor(20, 97);
		gameWindow << "[C] [3]                    - poruszanie sie na skos dol-prawo";
		gameWindow.MoveCursor(21, 97);
		gameWindow << "[spacja] [S] [5]           - zatwierdzenie i odsloniece pola";
		gameWindow.MoveCursor(22, 97);
		gameWindow << "[?]                        - zabezpieczenie pola, flaga";
		gameWindow.MoveCursor(27, 116);
		gameWindow.AttrOn(A_BOLD);
		gameWindow.AttrOn(green);
		gameWindow << "MILEJ ZABAWY :)";
		gameWindow.AttrOff(green);
		gameWindow.AttrOff(A_BOLD);
		Timer::getMutex()->unlock();
		int c;
		noecho();
		gameWindow >> c;
		echo();
		if (c == 27 || c == KEY_UP || c == KEY_DOWN) {
			show = false;
			break;
		}
	}
	if (!show) {
		Timer::getMutex()->lock();
		gameWindow.MoveCursor(1, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(3, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(4, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(5, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(6, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(7, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(8, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(11, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(13, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(14, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(15, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(16, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(17, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(18, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(19, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(20, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(21, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(22, 97);
		gameWindow << "                                                               ";
		gameWindow.MoveCursor(27, 116);
		gameWindow << "                                                               ";
		Timer::getMutex()->unlock();
		show = true;
	}
}