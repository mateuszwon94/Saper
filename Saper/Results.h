#pragma once
#include <string>
#include <fstream>
#include "Window.h"
class Results {
public:
	Results();
	void createFile(std::string name);
	~Results();
	static Results* getInstance();
	bool getProblem(){ return problem; }
	Results& operator<<(std::string text);
private:
	std::fstream file;
	static Results* _instance;
	bool problem;
};