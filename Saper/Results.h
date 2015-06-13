#pragma once
#include <string>
#include <fstream>
#include "Window.h"
#include <vector>
#include <algorithm>   
struct Pair {
	std::string rozmiar;
	int wynik;
};

class Results {
public:
	Results();
	void createFile(std::string name);
	~Results();
	static Results* getInstance();
	bool getProblem(){ return problem; }
	Results& operator<<(std::string text);
	void load();
	void view();
	std::fstream file;
private:
	void viewT();
	void viewF();
	bool show;
	int copy(int first, std::string text);
	Pair copy(std::string text, int first, int end);
	void sorting();
	std::vector<int> easy;
	std::vector<int> mild;
	std::vector<int> hard;
	std::vector<Pair> own30;
	std::vector<Pair> own70;
	std::vector<Pair> own;

	static Results* _instance;
	bool problem;
	//SORTOWANIE
};