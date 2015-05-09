#include "Help.h"
#include "Window.h"
#include <sstream>
#include <exception>

using namespace std;

Help* Help::_currentHelp = nullptr;

vector<string> &split(const string &s, char delim = ' ') {
	vector<string> elems = vector<string>();
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) 
		elems.push_back(item);
	return elems;
}

Help::Help(unsigned int posibleToWriteChars, unsigned int possibleToWriteLines, unsigned int line, unsigned int column) : _help(), _posLine(line), _posColumn(column), _posibleToWriteChars(posibleToWriteChars), _possibleToWriteLines(possibleToWriteLines) {
	_help["Saper"] = split("Gra polega na odkrywaniu na planszy poszczegolnych pol w taki sposob, aby nie natrafic na mina. Na kazdym z odkrytych pol napisana jest liczba min, które bezposrednio stykaj¹ siê z danym polem (od zera do osmiu). Jesli oznaczymy dane pole flag¹, jest ono zabezpieczone przed odslonieciem, dzieki czemu przez przypadek nie ods³onimy miny.");
	_help["Klawiszologia"] = split("[W], [8], [strzalka w gore] - przemieszczenie sie w gore.");

	if (_currentHelp != nullptr)
		delete _currentHelp;
	_currentHelp = this;
}

void Help::View() {
	gameWindow.MoveCursor(_posLine, _posColumn);
	gameWindow << "POMOC";
	int sign = 0;
	
	while (true) {
		int i = 0;
		for (size_t line = 0; line < _possibleToWriteLines; ++line) {
			gameWindow.MoveCursor(_posLine + 2 + line, _posColumn);
			unsigned int length = 0;
			try {
				while (true) {
					length += _help["Saper"].at(i).size();
					if (length > _posibleToWriteChars) continue;
					gameWindow << _help["Saper"].at(i);
					++i;
				}
			} catch (out_of_range& e) {
				try {
					while (true) {
						length += _help["Klawiszologia"].at(i).size();
						if (length > _posibleToWriteChars) continue;
						gameWindow << _help["Saper"].at(i);
						++i;
					}
				} catch (out_of_range& e) { return; }
			}

		}
	}
}

Help::~Help() { }