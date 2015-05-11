#include "Results.h"
using namespace std;
Results* Results::_instance = NULL;
Results::Results() {
	createFile("results.txt");
	problem = false;
}
void Results::createFile(std::string name) {
	file.open(name, std::ios::in | std::ios::app);
	if (file.good() != true) {
		problem = true;
		gameWindow.MoveCursor(1, 97);
		gameWindow << "Problem z plikiem";
	}
}
Results::~Results() {
	file.close();
}
Results* Results::getInstance() {
	if (_instance == NULL) _instance = new Results();
	return _instance;
}
Results& Results::operator<<(string text) {
	file << text;
	return *(this);
}
void Results::load() {
	string text;
	while (getline(file, text))
	{
		int first = 0;
		if (text[0] == 'l') {
			first = text.find_first_of(' ');
			int czas = copy(first, text);
			easy.push_back(czas);
		}
		else if (text[0] == 's') {
			first = text.find_first_of(' ');
			int czas = copy(first, text);
			mild.push_back(czas);
		}
		else if (text[0] == 't') {
			first = text.find_first_of(' ');
			int czas = copy(first, text);
			hard.push_back(czas);
		}
		else {
			//PRZEMYŒLE Z ROZMIARAMI PLANSZY!!!
		}
	}
}
int Results::copy(int first, string text) {
	char czas[4];
	std::size_t length = text.copy(czas, 4, first);
	czas[length] = '\0';
	int i_czas = atoi(czas);
}