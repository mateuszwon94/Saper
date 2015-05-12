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
			first = text.find_first_not_of('<');
			int end = text.find_first_not_of('>');
			string n ="";
			for (int i = first + 1; i < end; i++)
			{
				n += text[i];
			}
			int nr = stoi(n);
			if (nr < 30) 
				own30.push_back(copy(text,first,end));
			else if(nr >30 && nr < 70) 
				own70.push_back(copy(text, first, end));
			else 
				own.push_back(copy(text, first, end));

			//PRZEMYŒLE Z ROZMIARAMI PLANSZY!!!
		}
	}
}
int Results::copy(int first, string text) {
	char czas[4];
	#if defined(_SCL_SECURE_NO_WARNINGS)
	std::size_t length = text.copy(czas, 4, first);
	
	czas[length] = '\0';
	#endif
	int i_czas = atoi(czas);
	return i_czas;
}
Pair Results::copy(string text, int first, int end) {
	Pair elem;
	string w = "";
	for (int i = end + 1; i < text.length(); i++) w += text[i];
	elem.wynik = stoi(w);
	string roz = "";
	for (int i = 0; i < first; i++) roz += text[i];
	elem.rozmiar = roz;
	return elem;
}
bool compare(Pair a, Pair b) {
	if (a.wynik > b.wynik) return true; else return false;
}
bool compareI(int i, int j) {
	if (i > j) return true; else return false;
}
void Results::sorting() {
	sort(easy.begin(), easy.end(), compareI);
	sort(mild.begin(), mild.end(), compareI);
	sort(hard.begin(), hard.end(), compareI);
	sort(own30.begin(), own30.end(), compare);
	sort(own70.begin(), own70.end(), compare);
	sort(own.begin(), own.end(), compare);
}
void Results::view() {
	load();
	sorting();

}