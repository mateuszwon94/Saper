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