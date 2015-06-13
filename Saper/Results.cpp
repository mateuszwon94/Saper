#include "Results.h"
#include "Timer.h"
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
	file.clear();
	file.seekg(0, ios::beg);
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
			first = text.find_first_of('<');
			int end = text.find_first_of('>');
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
		}
	}
}
int Results::copy(int first, string text) {
	char czas[6];
	int i = 0;
	while (text[first] != '\n' && text[first] != '\0') {
		czas[i] = text[first];
		i++;
		first++;
	}
	czas[i] = '\0';
	int i_czas = atoi(czas);
	return i_czas;
}
Pair Results::copy(string text, int first, int end) {
	Pair elem;
	string w = "";
	for (int i = end + 1; i < text.length(); i++) w += text[i];
	elem.wynik = stoi(w);
	string roz = "";
	for (int i = 7; i < first; i++) roz += text[i];
	elem.rozmiar = roz;
	return elem;
}
bool compare(Pair a, Pair b) {
	if (a.wynik < b.wynik) return true; else return false;
}
bool compareI(int i, int j) {
	if (i < j) return true; else return false;
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
	show = true;
	while (show) {
		viewT();
		int c;
		noecho();
		gameWindow >> c;
		echo();
		if (c == 27 || c == KEY_UP || c == KEY_DOWN) {
			show = false;
			break;
		}
	}
	if (!show) viewF();
}
void Results::viewT() {
	Timer::getMutex()->lock();
	gameWindow.MoveCursor(1, 97+23);
	gameWindow.AttrOn(A_BOLD);
	static ColorPair green = ColorPair(COLOR_GREEN, COLOR_BLACK);
	gameWindow.AttrOn(A_BOLD);
	gameWindow.AttrOn(green);
	gameWindow << "NAJLEPSZE WYNIKI";
	gameWindow.MoveCursor(3, 97);
	gameWindow << "LATWY";
	gameWindow.AttrOff(green);
	gameWindow.AttrOff(A_BOLD);
	for (int i = 0; i < i < 10 && i < easy.size(); i++)
	{
		gameWindow.MoveCursor(4 + i, 97);
		gameWindow << easy[i]<< " s.";
	}
	gameWindow.MoveCursor(3, 97 + 22);
	gameWindow.AttrOn(A_BOLD);
	gameWindow.AttrOn(green);
	gameWindow << "SREDNI";
	gameWindow.AttrOff(green);
	gameWindow.AttrOff(A_BOLD);
	for (int i = 0; i < i < 10 && i < mild.size(); i++)
	{
		gameWindow.MoveCursor(4 + i, 97+22);
		gameWindow << mild[i] << " s.";
	}
	gameWindow.MoveCursor(3, 97 + 44);
	gameWindow.AttrOn(A_BOLD);
	gameWindow.AttrOn(green);
	gameWindow << "TRUDNY";
	gameWindow.AttrOff(green);
	gameWindow.AttrOff(A_BOLD);
	for (int i = 0; i < i < 10 && i < hard.size(); i++)
	{
		gameWindow.MoveCursor(4 + i, 97+44);
		gameWindow << hard[i] << " s.";
	}
	gameWindow.MoveCursor(15, 97);
	gameWindow.AttrOn(A_BOLD);
	gameWindow.AttrOn(green);
	gameWindow << "WLASNY BOMBY < 30";
	gameWindow.AttrOff(green);
	gameWindow.AttrOff(A_BOLD);
	for (int i = 0; i < i < 10 && i < own30.size(); i++)
	{
		gameWindow.MoveCursor(16 + i, 97);
		gameWindow << own30[i].rozmiar<<" " <<own30[i].wynik << " s.";
	}
	gameWindow.MoveCursor(15, 97+20);
	gameWindow.AttrOn(A_BOLD);
	gameWindow.AttrOn(green);
	gameWindow << "WLASNY 30 < BOMBY < 70";
	gameWindow.AttrOff(green);
	gameWindow.AttrOff(A_BOLD);
	for (int i = 0; i < i < 10 && i < own70.size(); i++)
	{
		gameWindow.MoveCursor(16 + i, 97+20);
		gameWindow << own70[i].rozmiar << " " << own70[i].wynik << " s.";
	}
	gameWindow.MoveCursor(15, 97+44);
	gameWindow.AttrOn(A_BOLD);
	gameWindow.AttrOn(green);
	gameWindow << "WLASNY BOMBY > 70";
	gameWindow.AttrOff(green);
	gameWindow.AttrOff(A_BOLD);
	for (int i = 0; i < i < 10 && i < own.size(); i++)
	{
		gameWindow.MoveCursor(16 + i, 97 + 44);
		gameWindow << own[i].rozmiar << " " << own[i].wynik << " s.";
	}
	Timer::getMutex()->unlock();
}
void Results::viewF(){
	easy.clear();
	mild.clear();
	hard.clear();
	own30.clear();
	own70.clear();
	own.clear();

	Timer::getMutex()->lock();
	for (int i = 0; i < 30;i++)
	{
		gameWindow.MoveCursor(i + 1, 97);
		gameWindow << "                                                              ";
	}
	Timer::getMutex()->unlock();
}