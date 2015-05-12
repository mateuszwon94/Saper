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
private:
	int copy(int first, std::string text);
	Pair copy(std::string text, int first, int end);
	void sorting();
	//bool compare(Pair a, Pair b);
	//bool compare(int i, int j);
	std::vector<int> easy;
	std::vector<int> mild;
	std::vector<int> hard;
	std::vector<Pair> own30;
	std::vector<Pair> own70;
	std::vector<Pair> own;
	std::fstream file;
	static Results* _instance;
	bool problem;
	//SORTOWANIE
};