#include "Help.h"
#include "Window.h"
#include <sstream>
#include <exception>

using namespace std;

//Help* Help::_currentHelp = nullptr;
//
//vector<string> &split(const string &s, char delim = ' ') {
//	vector<string> elems = vector<string>();
//	stringstream ss(s);
//	string item;
//	while (getline(ss, item, delim)) 
//		elems.push_back(item);
//	return elems;
//}

//Help::Help(unsigned int posibleToWriteChars, unsigned int possibleToWriteLines, unsigned int line, unsigned int column) : _help(), _posLine(line), _posColumn(column), _posibleToWriteChars(posibleToWriteChars), _possibleToWriteLines(possibleToWriteLines) {
//	_help["Saper"] = split("Gra polega na odkrywaniu na planszy poszczegolnych pol w taki sposob, aby nie natrafic na mina. Na kazdym z odkrytych pol napisana jest liczba min, które bezposrednio stykaj¹ siê z danym polem (od zera do osmiu). Jesli oznaczymy dane pole flag¹, jest ono zabezpieczone przed odslonieciem, dzieki czemu przez przypadek nie ods³onimy miny.");
//	_help["Klawiszologia"] = split("[W], [8], [strzalka w gore] - przemieszczenie sie w gore.");
//
//	if (_currentHelp != nullptr)
//		delete _currentHelp;
//	_currentHelp = this;
//}

void Help::View() {
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
	//int sign = 0;
	//
	//while (true) {
	//	int i = 0;
	//	for (size_t line = 0; line < _possibleToWriteLines; ++line) {
	//		gameWindow.MoveCursor(_posLine + 2 + line, _posColumn);
	//		unsigned int length = 0;
	//		try {
	//			while (true) {
	//				length += _help["Saper"].at(i).size();
	//				if (length > _posibleToWriteChars) continue;
	//				gameWindow << _help["Saper"].at(i);
	//				++i;
	//			}
	//		} catch (out_of_range& e) {
	//			try {
	//				while (true) {
	//					length += _help["Klawiszologia"].at(i).size();
	//					if (length > _posibleToWriteChars) continue;
	//					gameWindow << _help["Saper"].at(i);
	//					++i;
	//				}
	//			} catch (out_of_range& e) { return; }
	//		}

	//	}
	//}
}

//Help::~Help() { }