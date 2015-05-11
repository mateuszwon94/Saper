#pragma once
#include <string>
#include <fstream>
#include "Window.h"
#include <vector>
class Results {
public:
	Results();
	void createFile(std::string name);
	~Results();
	static Results* getInstance();
	bool getProblem(){ return problem; }
	Results& operator<<(std::string text);
	void load();
private:
	int copy(int first, std::string text);
	std::vector<int> easy;
	std::vector<int> mild;
	std::vector<int> hard;
	std::vector<int> own;
	std::fstream file;
	static Results* _instance;
	bool problem;
	//SORTOWANIE
};